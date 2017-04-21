// ChatRoom.cpp
//

#include "ChatRoom.h"
#include "zlib.h"

long hex2dec(char * s)
{
	int L = (int)strlen(s);
	char c;
	long re = 0;
	while (c = s++[0])
	{
		if (c >= '0' && c <= '9')
		{
			c -= 48;
		}		
		else
		{
			c = c>'Z' ? c - 32 : c;
			c -= 'A' - 10;
		}
		re += c*pow(16.0, --L);
	}

	return re;
}

std::string unescape(char* str)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	const int nMultiByte = 2;
#else
	setlocale(LC_CTYPE, "zh_CN.UTF-8");
	const int nMultiByte = 3;
    	int nByte = 0;
#endif

	char* re = (char*)calloc(strlen(str) + 1, 1);
	char* _str;
	char* _re = re;
	char code[5] = { 0 };
	wchar_t wc;
	int n;

	while (str)
	{
		_str = strchr(str, '%');
		if (!_str)
		{
			break;
		}

		if (n = _str - str)
		{
			memcpy(_re, str, n);
			_re += n;
		}

		memset(code, 0, sizeof(code));
		if (_str[1] == 'u')
		{
			memcpy(code, _str + 2, 4);
			str = _str + 6;
			wc = hex2dec(code);
			memset(code, 0, 5);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			WideCharToMultiByte(CP_OEMCP, NULL, &wc, -1, (char*)code, nMultiByte, NULL, FALSE);
#else
			wcstombs(code, &wc, nMultiByte);
#endif
            		nByte = (int)strlen(code);
			memcpy(_re, code, nByte);
			_re += nByte;
		}
		else
		{
			memcpy(code, _str + 1, 2);
			str = _str + 3;
			_re[0] = hex2dec(code);
			_re++;
		}
	}

	strcpy(_re, str);
	std::string rt(re);
	free(re);
	re = NULL;

	return rt;
}

CChatRoom::CChatRoom(IChatRoomObserver* pObserver)
{
	m_pObserver = pObserver;
	m_pLink = NULL;

	m_bEnter = false;
	m_bConnect = false;
	m_nKeepLiveTimer = 0;
	m_nMasterId = "";
	m_nRoomId = "";
	m_nRoomPort = 0;

	m_strToken.clear();
	m_strChatMsg = "";
	m_eMsgType = CR_MSG;

	m_SynchMutex = PTHREAD_MUTEX_INITIALIZER;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_hEnter = CreateEvent(NULL, TRUE, FALSE, NULL);
#else
	sem_init(&m_semEnter, 0, 0);
#endif
}

CChatRoom::~CChatRoom()
{
	StopTimer(m_nKeepLiveTimer);

	if (m_pLink)
	{
		m_pLink->Close();
		m_pLink->Release();
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	CloseHandle(m_hEnter);
#else
	sem_destroy(&m_semEnter);
#endif
}

void CChatRoom::SetToken(std::string strToken)
{
	m_strToken = strToken;
}


void CChatRoom::SetChatRoomInfo(ChatRoomInfo RoomInfo)
{
	m_nRoomId	= RoomInfo.nRoomId;
	m_nRoomPort = RoomInfo.nPort;
	m_nMasterId = RoomInfo.nMasterId;
	
	for (long i = 0; i < MAX_CHAT_NODE; i++)
	{
		m_strRoomIp[i] = RoomInfo.strIp[i];
	}
    
    
    printf("##### %s,%s", m_nRoomId.c_str(), m_nMasterId.c_str());
}

void CChatRoom::OpenTCPLink(long nNodeNum)
{
	if (m_pLink)
	{
		m_pLink->Close();
		m_pLink->Release();
		m_pLink = NULL;
	}

	int nTry = 0;
	m_bConnect = false;
	while (nTry++ < 3)
	{
		m_pLink = new CRawLink();
		if (g_pLink != m_pLink){ g_pLink = m_pLink; }
		m_pLink->AttachSink(this);

		bool bRet = m_pLink->Open(m_strRoomIp[nNodeNum].c_str(), m_nRoomPort);
		if (bRet)
		{
			m_bConnect = true;
			break;
		}

		if (m_pLink)
		{
			m_pLink->Close();
			m_pLink->Release();
			m_pLink = NULL;
		}
	}
}

long CChatRoom::EnterChatRoom()
{
	if (m_bEnter)
	{
		return 0;
	}

	long nNodeNum = 0;
	{
		pthread_mutex_lock(&m_SynchMutex);

		while (nNodeNum < MAX_CHAT_NODE)
		{
			OpenTCPLink(nNodeNum);
			if (!m_bConnect){ nNodeNum++; }
			else{ break; }
		}

		if (!m_bConnect)
		{
			m_strChatMsg = ERR_CONNECT_FAILD;
			m_eMsgType = CR_ERROR;
			m_pObserver->OnError(1, "");
			ExitChatRoom();
			return 0;
		}

		std::string jsonEnter = "{\"_method_\":\"Enter\",\"type\":\"0\",\"rid\":\"";
		jsonEnter += m_nRoomId;
		jsonEnter += "\",\"uid\":\"";
		jsonEnter += m_nMasterId;
		jsonEnter += "\",\"uname\":\"hehe\",\"token\":\"";
		jsonEnter += m_strToken;
		//jsonEnter += "\",\"md5\":\"RTYUI\",\"majorType\":\"0\",\"terminal\":\"2\"}";
        jsonEnter += "\",\"md5\":\"RTYUI\",\"majorType\":\"0\",\"terminal\":\"2\",\"v\":\"0\"}";

		CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonEnter.c_str(), (int)jsonEnter.length());
		pPacket->SetPacketType(0);
        pPacket->SetPacketAction(0);
		m_pLink->SendPacket(pPacket);

		pthread_mutex_unlock(&m_SynchMutex);
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	unsigned long dwCode = ::WaitForSingleObject(m_hEnter, MAX_WAIT_TIME * MULTIPLENUM);
	if (dwCode != WAIT_OBJECT_0)
	{
		m_strChatMsg = ERR_ENTER_FAILD;
		m_eMsgType = CR_ERROR;
		m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
		return 0;
	}

	m_nKeepLiveTimer = StartTimer(true, KEEPLIVE_INTERVAL * MULTIPLENUM, 50);
#else

//	clock_gettime(CLOCK_REALTIME, &m_tOutTime);
//	m_tOutTime.tv_sec += MAX_WAIT_TIME;
//    int nRet = 0;//sem_timedwait(&m_semEnter, &m_tOutTime);
//	if (nRet == -1)
//	{
//		m_eMsgType = CR_ERROR;
//		m_strChatMsg = ERR_ENTER_FAILD;
//		m_pObserver->OnError(1,"");
//		return 0;
//	}

	//signal(SIGALRM, CChatRoom::OnTimer);
	//alarm(KEEPLIVE_INTERVAL);
#endif

	m_bEnter = true;
	return nNodeNum;
}

void CChatRoom::UserList() {
    pthread_mutex_lock(&m_SynchMutex);
    std::string jsonUserList = "{\"pno\":\"1\",\"rpp\":\"40\",\"v\":\"0\"}";
    
    CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonUserList.c_str(), (int)jsonUserList.length());
    pPacket->SetPacketAction(0);
    pPacket->SetPacketType(6);
    m_pLink->SendPacket(pPacket);
    pthread_mutex_unlock(&m_SynchMutex);
}

long CChatRoom::Speak(std::string words, std::string uid, bool ispublic) {
    pthread_mutex_lock(&m_SynchMutex);
    
    if(uid == "0") {  //to all the room users; ispublic is to all
        std::string jsonSpeaker = "{\"_method_\":\"SendPubMsg\",\"toMasterId\":\"";
        //jsonSpeaker += uid;
        jsonSpeaker += "\",\"toMasterNick\":\"\"";
        jsonSpeaker += ",\"ct\":\"" ;
        jsonSpeaker += words;
        jsonSpeaker += "\"}";
        
        CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonSpeaker.c_str(), (int)jsonSpeaker.length());
        pPacket->SetPacketAction(0);
        pPacket->SetPacketType(2);
        m_pLink->SendPacket(pPacket);
        
        
    }else {      // to somebody
        if(ispublic) {  //
            std::string jsonSpeaker = "{\"_method_\":\"SendPubMsg\",\"toMasterId\":\"";
            //jsonSpeaker += uid;
            jsonSpeaker += "\",\"toMasterNick\":\"\"";
            jsonSpeaker += ",\"ct\":\"" ;
            jsonSpeaker += words;
            jsonSpeaker += "\"}";
            
            
            
            CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonSpeaker.c_str(), (int)jsonSpeaker.length());
            printf("%s,%s,%s", m_nRoomId.c_str(),m_nMasterId.c_str(),jsonSpeaker.c_str());
            pPacket->SetPacketAction(0);
            pPacket->SetPacketType(2);
            m_pLink->SendPacket(pPacket);
        } else {
            std::string jsonSpeaker = "{\"_method_\":\"SendPubMsg\",\"toMasterId\":\"";
            jsonSpeaker += uid;
            jsonSpeaker += "\",\"toMasterNick\":\"\",\"rid\":\"";
            jsonSpeaker += m_nRoomId;
            jsonSpeaker += "\",\"uid\":\"";
            jsonSpeaker += m_nMasterId;
            jsonSpeaker += "\",\"ct\":\"" ;
            jsonSpeaker += words;
            jsonSpeaker += "\",\"pub\":\"0\",\"key\":\"\",\"code\":\"\",\"checksum\":\"\",\"v\",\"0\"}";
            
            CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonSpeaker.c_str(), (int)jsonSpeaker.length());
            pPacket->SetPacketAction(0);
            pPacket->SetPacketType(2);
            m_pLink->SendPacket(pPacket);
        }
    }
    pthread_mutex_unlock(&m_SynchMutex);

    return 1;
}

long CChatRoom::ReentryChatRoom(long nNodeNum)
{
    if (m_bEnter)
	{
		return nNodeNum;
	}

	{
		pthread_mutex_lock(&m_SynchMutex);

		OpenTCPLink(nNodeNum);
		if (!m_bConnect){ return EnterChatRoom(); }

		std::string jsonEnter = "{\"_method_\":\"Enter\",\"type\":\"0\",\"rid\":\"";
		jsonEnter += m_nRoomId;
		jsonEnter += "\",\"uid\":\"";
		jsonEnter += m_nMasterId;
		jsonEnter += "\",\"uname\":\"hehe\",\"token\":\"";
		jsonEnter += m_strToken;
		//jsonEnter += "\",\"md5\":\"RTYUI\",\"majorType\":\"0\",\"terminal\":\"2\"}";
        jsonEnter += "\",\"md5\":\"RTYUI\",\"majorType\":\"0\",\"terminal\":\"2\"}";

		CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonEnter.c_str(), jsonEnter.length());
        pPacket->SetPacketAction(0);
		pPacket->SetPacketType(0);
		m_pLink->SendPacket(pPacket);

		pthread_mutex_unlock(&m_SynchMutex);
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	unsigned long dwCode = ::WaitForSingleObject(m_hEnter, MAX_WAIT_TIME * MULTIPLENUM);
	if (dwCode != WAIT_OBJECT_0)
	{
		m_strChatMsg = ERR_REENTRY_FAILD;
		m_pObserver->OnChatRoom(CR_ERROR, m_strChatMsg);
		return nNodeNum;
	}

	m_nKeepLiveTimer = StartTimer(true, KEEPLIVE_INTERVAL * MULTIPLENUM, 50);
#else

	clock_gettime(CLOCK_REALTIME, &m_tOutTime);
	m_tOutTime.tv_sec += MAX_WAIT_TIME;
    int nRet = 0;//sem_timedwait(&m_semEnter, &m_tOutTime);
	if (nRet == -1)
	{
		m_eMsgType = CR_ERROR;
		m_strChatMsg = ERR_REENTRY_FAILD;
		m_pObserver->OnError(1, "");
		return nNodeNum;
	}

	//signal(SIGALRM, CChatRoom::OnTimer);
	//alarm(KEEPLIVE_INTERVAL);
#endif

	m_bEnter = true;
	return nNodeNum;
}

void CChatRoom::ExitChatRoom()
{
	if (!m_bEnter)
	{
		return;
	}

	m_bEnter = false;
	//StopTimer(m_nKeepLiveTimer);

	if (m_pLink != NULL)
	{
		m_pLink->Close();
		m_pLink->Release();
		m_pLink = NULL;
	}
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

bool CChatRoom::OnTimer(int nTimeID)
{
	if (nTimeID == m_nKeepLiveTimer)
	{
		pthread_mutex_lock(&m_SynchMutex);

		time_t tStamp = time(NULL);

		std::string HreatBeat = "{\"randomNumber\":\"";
		HreatBeat += std::to_string(tStamp);
		HreatBeat += "\",\"v\":\"0\"}";

		CPacket* pPacket = CPacket::CreateFromPayload((char*)HreatBeat.c_str(), HreatBeat.length());
		pPacket->SetPacketType(KEEPLIVE);
		if (m_pLink)
		{
			m_pLink->SendPacket(pPacket);
		}

		pthread_mutex_unlock(&m_SynchMutex);
	}
	return true;
}

#else

void CChatRoom::OnTimer(long nTimeId)
{
	time_t tStamp = time(NULL);

	std::string HreatBeat = "{\"randomNumber\":\"";
	HreatBeat += std::to_string(tStamp);
	HreatBeat += "\",\"v\":\"0\"}";

	CPacket* pPacket = CPacket::CreateFromPayload((char*)HreatBeat.c_str(), HreatBeat.length());
	pPacket->SetPacketType(KEEPLIVE);
	if (g_pLink)
		g_pLink->SendPacket(pPacket);

	//alarm(KEEPLIVE_INTERVAL);
}
#endif

void CChatRoom::OnLinkErr(CRawLink* pLink)
{
	if (pLink != m_pLink)
	{
		return;
	}

	pthread_mutex_lock(&m_SynchMutex);

	m_bEnter = false;
	//StopTimer(m_nKeepLiveTimer);

	if (m_pLink != NULL)
	{
		m_pLink->Close();
		m_pLink->Release();
		m_pLink = NULL;
	}

	m_strChatMsg = MSG_RECONNECT_CHAT;
	m_eMsgType = CR_RECONNECT;
	m_pObserver->OnError(1,"");

	pthread_mutex_unlock(&m_SynchMutex);
}

void CChatRoom::OnLinkPacket(CRawLink* pLink, CPacket* pPacket)
{
	if (pPacket == NULL)
	{
		return;
	}
    
    time_t rawtime;
    time ( &rawtime );
    this->lastPackTime = rawtime;
    
    printf("chatroom: type %d, %d\n", pPacket->GetPacketType() >> 16, pPacket->GetPacketType() & 0xffff);

	if (pPacket->GetPacketType() == ((3<<16) + 0))
	{
        printf("receive 3,0\n");
		return;
	}

	uLongf dlen = sizeof(char)* (MAX_BUF_SIZE);
	char* dbuf = (char*)malloc(dlen);
	memset(dbuf, 0, dlen);
	int nRet = uncompress((Bytef*)dbuf, &dlen, (Bytef*)pPacket->GetPayload(), pPacket->GetPacketSize());
	while (nRet != Z_OK)
	{
		if (dlen / MAX_BUF_SIZE > 10)
		{
			break;
		}

		dlen *= 2;
		free(dbuf);
		dbuf = (char*)malloc(dlen);
		memset(dbuf, 0, dlen);
		nRet = uncompress((Bytef*)dbuf, &dlen, (Bytef*)pPacket->GetPayload(), pPacket->GetPacketSize());
	}
    
    
//    printf("comming: %s\n",dbuf);
    
    PtlBase* protocol = PtlBase::getProtocol(dbuf);
    
    if(protocol == NULL) {
        return ;
    }
    
    switch(protocol->getRetCode()){
        case 0: // ok
//            printf("****** ok \n");
            if(protocol->isMsg()) {
                m_pObserver->OnMsg(protocol);
            }
            break;
        case 1: // error
            break;
        case 2:
            break;
        case 401001:
            break;
        case 401002:
            break;
        case 401005:  // invalid roomid
            m_pObserver->OnError(401005, "");
            break;
        case 401007:
            break;
        case 401011:
            break;
        case 401014:
            break;
        case 402001:
            break;
        case 402003:
            break;
        case 402004:
            break;
        case 402005:
            break;
        case 402007:
            break;
        case 402008:
            break;
        case 402009:
            break;
        case 402010:
            break;
        case 402012:
            break;
        case 402013:
            break;
        case 402014:
            break;
        case 402015:
            break;
        case 402016:
            break;
        case 402017:
            break;
        case 403001:
            break;
        case 403002:
            break;
        case 404001:
            break;
        case 404002:
            break;
        case 409004:
            if (m_pObserver)
            {
                m_eMsgType = CR_ERROR;
                m_strChatMsg = ERR_REPETITION_LOGIN;
                m_pObserver->OnError(1,"");
                ExitChatRoom();
            }
            return;
        case 409005:
            break;
            
    }

    
	if (dbuf)
	{
		free(dbuf);
	}

	return;
}

long CChatRoom::AddRef()
{
	return CRefCount::AddRef();
}

long CChatRoom::Release()
{
	return CRefCount::Release();
}

std::string CChatRoom::GetErrMsg()
{
	return m_strChatMsg;
}

bool CChatRoom::IsEntered()
{
	return m_bEnter;
}

bool CChatRoom::IsConnect()
{
	return m_bConnect;
}

#define STACK_ARRAY(TYPE, LEN) static_cast<TYPE*>(::alloca((LEN)*sizeof(TYPE)))
std::string CChatRoom::TransCode(const std::string& strUtf8)
{
	int nLen = strUtf8.size() * 4;
	char* pANSI = STACK_ARRAY(char, nLen);
	Utf_8ToANSI(strUtf8.c_str(), strUtf8.size(), pANSI, &nLen);
	std::string strANSI = pANSI;
	strANSI.assign(pANSI, nLen);
	return strANSI;
}

bool CChatRoom::Utf_8ToANSI(const char* pUtf8, int nUtf_8Len, char* pANSI, int* ANSILen)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	int nUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, pUtf8, nUtf_8Len, NULL, 0);
	wchar_t* pUnicode = new wchar_t[nUnicodeLen + 1];
	memset(pUnicode, 0, nUnicodeLen * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, pUtf8, nUtf_8Len, pUnicode, nUnicodeLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pUnicode, nUnicodeLen, NULL, 0, NULL, NULL);
	if (*ANSILen < nLen)
	{
		return false;
	}

	memset(pANSI, 0, *ANSILen);
	WideCharToMultiByte(CP_ACP, 0, pUnicode, nUnicodeLen, pANSI, nLen, NULL, NULL);
	*ANSILen = nLen;

	delete[] pUnicode;

#endif
	return true;
}

std::string CChatRoom::EscapeCode(std::string& str)
{
	EscapeCode(str, "&amp;", "&");
	EscapeCode(str, "&nbsp;", " ");
	EscapeCode(str, "&middot;", "°§");
	EscapeCode(str, "&rsquo;", "'");
	EscapeCode(str, "&lsquo;", "'");
	EscapeCode(str, "&ldquo;", "\"");
	EscapeCode(str, "&rdquo;", "\"");
	EscapeCode(str, "&quot;", "\"");
	EscapeCode(str, "&mdash;", "°™");
	EscapeCode(str, "&hellip;", "°≠°≠");
	EscapeCode(str, "&lt;", "<");
	EscapeCode(str, "&rarr;", "°˙");
	EscapeCode(str, "&cap;", "°…");

	return str;
}

bool CChatRoom::EscapeCode(std::string& str, std::string oldchar, std::string newchar)
{
	std::string::size_type pos = str.find(oldchar);
	while (pos != std::string::npos)
	{
		str.replace(pos, oldchar.size(), newchar);
		pos = str.find(oldchar);
	}

	return true;
}
