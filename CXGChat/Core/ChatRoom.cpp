// ChatRoom.cpp
//

#include "ChatRoom.h"

long hex2dec(char * s)
{
	int L = strlen(s);
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		_strset_s(code, 0);
#else
		memset(code, '0', 5);
#endif
		if (_str[1] == 'u')
		{
			memcpy(code, _str + 2, 4);
			str = _str + 6;
			wc = hex2dec(code);
			memset(code, 0, 5);
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				WideCharToMultiByte(CP_OEMCP, NULL, &wc, -1, (char*)code, 2, NULL, FALSE);
			#else
				const wchar_t* cwc = &wc;
				wcstombs(code,cwc,5);
			#endif
			memcpy(_re, code, 2);
			_re += 2;
		}
		else
		{
			memcpy(code, _str + 1, 2);
			str = _str + 3;
			_re[0] = hex2dec(code);
			_re++;
		}
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	strcpy_s(_re, strlen(_re), str);
#else
	strcpy(_re, str);
#endif
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
	m_nMasterId = 0;
	m_nRoomId = 0;
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
	
	for (int i = 0; i < MAX_CHAT_NODE; i++)
	{
		m_strRoomIp[i] = RoomInfo.strIp[i];
	}
}

void CChatRoom::OpenTCPLink(int nNodeNum)
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

int CChatRoom::EnterChatRoom()
{
	if (m_bEnter)
	{
		return 0;
	}

	int nNodeNum = 0;
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
			m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
			ExitChatRoom();
			return 0;
		}

		std::string jsonEnter = "{\"_method_\":\"Enter\",\"type\":\"0\",\"rid\":\"";
		jsonEnter += m_nRoomId;
		jsonEnter += "\",\"uid\":\"";
		jsonEnter += m_nMasterId;
		jsonEnter += "\",\"uname\":\"hehe\",\"token\":\"";
		jsonEnter += m_strToken;
		jsonEnter += "\",\"md5\":\"RTYUI\",\"majorType\":\"0\",\"terminal\":\"1\"}";

		CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonEnter.c_str(), jsonEnter.length());
		pPacket->SetPacketType(0);
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

	clock_gettime(CLOCK_REALTIME, &m_tOutTime);
	m_tOutTime.tv_sec += MAX_WAIT_TIME;
	int nRet = sem_timedwait(&m_semEnter, &m_tOutTime);
	if (nRet == -1)
	{
		m_eMsgType = CR_ERROR;
		m_strChatMsg = ERR_ENTER_FAILD;
		m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
		return 0;
	}

	signal(SIGALRM, CChatRoom::OnTimer);
	alarm(KEEPLIVE_INTERVAL);
#endif

	m_bEnter = true;
	return nNodeNum;
}

int CChatRoom::ReentryChatRoom(int nNodeNum)
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
		jsonEnter += "\",\"md5\":\"RTYUI\",\"majorType\":\"0\",\"terminal\":\"1\"}";

		CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonEnter.c_str(), jsonEnter.length());
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
	int nRet = sem_timedwait(&m_semEnter, &m_tOutTime);
	if (nRet == -1)
	{
		m_eMsgType = CR_ERROR;
		m_strChatMsg = ERR_REENTRY_FAILD;
		m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
		return nNodeNum;
	}

	signal(SIGALRM, CChatRoom::OnTimer);
	alarm(KEEPLIVE_INTERVAL);
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
	StopTimer(m_nKeepLiveTimer);

	if (m_pLink)
	{
		m_pLink->Close();
		m_pLink->Release();
		m_pLink = NULL;
	}
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

bool CChatRoom::OnTimer(int nTimeID)
{
	bool bRet = true;

	if (nTimeID == m_nKeepLiveTimer)
	{
		pthread_mutex_lock(&m_SynchMutex);

		time_t tStamp = time(NULL);
		char sTimeStamp[50];
		ctime_s(sTimeStamp, 50, &tStamp);
		CPacket* pPacket = CPacket::CreateFromPayload(sTimeStamp, strlen(sTimeStamp));
		pPacket->SetPacketType(KEEPLIVE);
		if (m_pLink)
		{
			m_pLink->SendPacket(pPacket);
		}

		pthread_mutex_unlock(&m_SynchMutex);
	}

	return bRet;
}

#else

void CChatRoom::OnTimer(int nTimeId)
{
	time_t tStamp;
	time(&tStamp);
	char sTimeStamp[50];
	sprintf(sTimeStamp,"%l",tStamp);
	CPacket* pPacket = CPacket::CreateFromPayload(sTimeStamp, strlen(sTimeStamp));
	pPacket->SetPacketType(KEEPLIVE);
	if (g_pLink)
		g_pLink->SendPacket(pPacket);

	alarm(KEEPLIVE_INTERVAL);
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
	StopTimer(m_nKeepLiveTimer);

	if (m_pLink != NULL)
	{
		m_pLink->Close();
		m_pLink->Release();
		m_pLink = NULL;
	}

	m_strChatMsg = MSG_RECONNECT_CHAT;
	m_eMsgType = CR_RECONNECT;
	m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);

	pthread_mutex_unlock(&m_SynchMutex);
}

void CChatRoom::OnLinkPacket(CRawLink* pLink, CPacket* pPacket)
{
	if (pPacket == NULL)
	{
		return;
	}

	if (pPacket->GetPacketType() == KEEPLIVE)
	{
		return;
	}

	uLongf dlen = sizeof(char)* (2048);
	char* dbuf = (char*)malloc(dlen);
	memset(dbuf, 0, dlen);
	int nRet = uncompress((Bytef*)dbuf, &dlen, (Bytef*)pPacket->GetPayload(), pPacket->GetPacketSize());
	while (nRet != Z_OK)
	{
		if (dlen / 2048 > 10)
		{
			break;
		}

		dlen *= 2;
		free(dbuf);
		dbuf = (char*)malloc(dlen);
		memset(dbuf, 0, dlen);
		nRet = uncompress((Bytef*)dbuf, &dlen, (Bytef*)pPacket->GetPayload(), pPacket->GetPacketSize());
	}

	Json::Reader reader;
	Json::Value object;

	try
	{
		if (!reader.parse(dbuf, object))
		{
			return;
		}
	}
	catch (std::exception& e)
	{
		return;
	}

	std::string code = object["retcode"].asString();

	if (code == "409004")
	{
		std::string timestamp = object["rettime"].asString();
		if (m_pObserver)
		{
			m_eMsgType = CR_ERROR;
			m_strChatMsg = ERR_REPETITION_LOGIN;
			m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
			ExitChatRoom();
		}
		return;
	}

	if (code != "000000")
	{
		std::string strMsg = object["retmsg"].asString();
		m_eMsgType = CR_ERROR;
		m_strChatMsg = ERR_UNKNOW_ERROR;
		m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
		return;
	}

	Json::Value msgObj = object["msg"];
	if (!msgObj.empty())
	{
		Json::Value::iterator itc = msgObj.begin();
		std::string action = (*itc)["b"].asString();
		std::string msgtype = (*itc)["c"].asString();
		int nMsgType = atoi(msgtype.c_str());

		switch (nMsgType)
		{
		case 0:
		{
				  if (action == "0") // 上线通知
				  {
					  Json::Value ctObj = (*itc)["ct"];
					  std::string masterId;
					  long long nMasterId = 0;
					  if (!ctObj.empty())
					  {
						  //masterNick = TransCode::Utf_8ToANSI(ctObj["masterNick"].asString());
						  masterId = ctObj["bb"].asString();
						  const char* cMasterId = masterId.c_str();
						  #if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
							 nMasterId = _atoi64(cMasterId);
						  #else
						     nMasterId = strtoll(cMasterId, NULL, 10 );
						  #endif
					  }

					  if (nMasterId == m_nMasterId && m_pObserver)
					  {
					      #if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
							 SetEvent(m_hEnter);
						  #else
							 sem_post(&m_semEnter);
						  #endif
							 m_eMsgType = CR_USERADD;
							 m_strChatMsg = MSG_USER_ENTER;
							 m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
					  }
				  }
				  else if (action == "1")  // 退出消息
				  {
					  Json::Value ctObj = (*itc)["ct"];
					  std::string masterId;
					  long long nMasterId = 0;
					  if (!ctObj.empty())
					  {
						  masterId = ctObj["bb"].asString();
						  const char* cMasterId = masterId.c_str();
					      #if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
							 nMasterId = _atoi64(cMasterId);
						  #else
							 nMasterId = strtoll(cMasterId, NULL, 10);
						  #endif
					  }

					  if (nMasterId == m_nMasterId && m_pObserver)
					  {
						  m_eMsgType = CR_USERDEL;
						  m_strChatMsg = MSG_USER_EXIT;
						  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
						  m_eMsgType = CR_LIVE_STOP;
						  m_strChatMsg = MSG_LIVE_STOP;
						  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
						  ExitChatRoom();
					  }
				  }
		}
			break;

		case 1:
		{
				  if (action == "3") //展示礼物
				  {
					  std::string strct = (*itc)["ct"].asString();
					  strct = unescape((char*)strct.c_str());
					  Json::Reader ctreader;
					  Json::Value ctobject;
					  std::string strMsg = "送礼：";
					  if (ctreader.parse(strct.c_str(), ctobject))
					  {
						  strMsg += ctobject["userName"].asString();
						  strMsg += "送给";
						  strMsg += ctobject["toUserName"].asString();
						  strMsg += " ";
						  strMsg += ctobject["giftCount"].asUInt();
						  strMsg += "个";
						  strMsg += ctobject["giftName"].asString();
					  }

					  if (m_pObserver)
					  {
						  m_eMsgType = CR_PRESENT;
						  m_strChatMsg = strMsg.c_str();
						  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
					  }
				  }
				  else if (action == "15") // 直播推流成功
				  {
					  Json::Value ctObj = (*itc)["ct"];
					  std::string masterId;
					  long long nMasterId = 0;
					  if (!ctObj.empty())
					  {
						  masterId = ctObj["bb"].asString();
						  const char* cMasterId = masterId.c_str();
						#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
						  nMasterId = _atoi64(cMasterId);
						#else
						  nMasterId = strtoll(cMasterId, NULL, 10);
						#endif
					  }

					  if (nMasterId == m_nMasterId)
					  {
						  if (m_pObserver)
						  {
							  m_eMsgType = CR_LIVE_OK;
							  m_strChatMsg = MSG_LIVE_OK;
							  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
						  }
					  }
				  }
				  else if (action == "18")  // 直播关闭
				  {
					  int closeType = 0;
					  Json::Value ctObj = (*itc)["ct"];
					  std::string masterId;
					  long long nMasterId = 0;

					  if (!ctObj.empty())
					  {
						  masterId = ctObj["bb"].asString();
						  const char* cMasterId = masterId.c_str();
						  
						#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
						  nMasterId = _atoi64(cMasterId);
						#else
						  nMasterId = strtoll(cMasterId, NULL, 10);
						#endif
						  closeType = ctObj["a"].asInt();
					  }

					  if (nMasterId == m_nMasterId)
					  {
						  if (m_pObserver)
						  {
							  if (closeType)
							  {
								  m_eMsgType = CR_LIVE_STOP;
								  m_strChatMsg = ERR_UPLOAD_FAILD;
							  }
							  else
							  {
								  m_eMsgType = CR_LIVE_STOP;
								  m_strChatMsg = MSG_LIVE_STOP;
							  }
							  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
						  }
						  ExitChatRoom();
					  }
				  }
				  else if (action == "24")
				  {
					  std::string strct = (*itc)["ct"].asString();
					  strct = unescape((char*)strct.c_str());
					  Json::Reader ctreader;
					  Json::Value ctobject;
					  if (ctreader.parse(strct.c_str(), ctobject))
					  {
						  int broad = ctobject["broad"].asInt();
						  std::string strMsg = "系统：";
						  strMsg += ctobject["mes"].asString();

						  if (m_pObserver && broad != 1)
						  {
							  m_eMsgType = CR_SYSMSG;
							  m_strChatMsg = strMsg.c_str();
							  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
						  }
					  }
				  }
				  else if (action == "30") // 直播推流中断
				  {
					  Json::Value ctObj = (*itc)["ct"];
					  std::string masterId;
					  std::string streamName;
					  long long nMasterId = 0;
					  if (!ctObj.empty())
					  {
						  masterId = ctObj["masterId"].asString();
						  const char* cMasterId = masterId.c_str();
						#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
						  nMasterId = _atoi64(cMasterId);
						#else
						  nMasterId = strtoll(cMasterId, NULL, 10);
						#endif

						  if (ctObj.isMember("streamName"))
						  {
							  streamName = ctObj["streamName"].asString();
						  }
					  }

					  if (nMasterId == m_nMasterId)
					  {
						  if (m_pObserver)
						  {
							  m_eMsgType = CR_LIVE_INTERRUPT;
							  m_strChatMsg = MSG_LIVE_INTERRUPT;
							  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
							  //m_pObserver->OnChatRoom(CR_MSG, streamName);
						  }
					  }
				  }
				  else if (action == "34") // 直播推流失败
				  {
					  Json::Value ctObj = (*itc)["ct"];
					  std::string masterId;
					  long long nMasterId = 0;
					  if (!ctObj.empty())
					  {
						  masterId = ctObj["masterId"].asString();
						  const char* cMasterId = masterId.c_str();
						#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
						  nMasterId = _atoi64(cMasterId);
						#else
						  nMasterId = strtoll(cMasterId, NULL, 10);
						#endif
					  }

					  if (nMasterId == m_nMasterId)
					  {
						  if (m_pObserver)
						  {
							  m_eMsgType = CR_LIVE_FAIL;
							  m_strChatMsg = MSG_LIVE_FAILD;
							  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
						  }
					  }
				  }
		}
			break;
		case 2:
		{
				  //std::string strMsg = TransCode((*itc)["masterNick"].asString());
				  //std::string strct = TransCode((*itc)["ct"].asString());
				  std::string strMsg = (*itc)["masterNick"].asString();
				  std::string strct = (*itc)["ct"].asString();
				  std::string strContent = EscapeCode(strct);

				  if (action == "0") // 公聊
				  {
					  strMsg += "说：";
				  }
				  else if (action == "1") // 公开的私聊
				  {
					  strMsg += "对";
					  strMsg += unescape((char*)(*itc)["toMasterNick"].asString().c_str());
					  strMsg += "说：";
				  }
				  else if (action == "2") // 私聊
				  {
					  strMsg += "对你说：";
				  }
				  else if (action == "3") // 弹幕
				  {
					  return;
				  }

				  strMsg += strContent;
				  if (m_pObserver)
				  {
					  m_eMsgType = CR_SPEAK;
					  m_strChatMsg = strMsg.c_str();
					  m_pObserver->OnChatRoom(CR_SPEAK, m_strChatMsg);
				  }
		}
			break;
		case 6:
		{
				  if (action == "0") // 用户列表
				  {
					  Json::Value ctObj = (*itc)["ct"];
					  Json::Value::iterator ict = ctObj.begin();
					  int ncount = (*ict)["e"].asInt();

					  if (m_pObserver)
					  {
						  m_eMsgType = CR_USERLIST;
						  m_strChatMsg = " ";
						  m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
					  }
				  }
		}
			break;
		case 11:
		{
				   if (action == "0") // 矫正人数
				   {
					   Json::Value ctObj = (*itc)["ct"];
					   std::string strMsg = ctObj["currentRoomUserCount"].asString();
					   if (m_pObserver)
					   {
						   m_eMsgType = CR_USERCOUNT;
						   m_strChatMsg = strMsg.c_str();
						   m_pObserver->OnChatRoom(m_eMsgType, m_strChatMsg);
					   }
				   }
		}
			break;

		default:
			break;
		}
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
	EscapeCode(str, "&middot;", "·");
	EscapeCode(str, "&rsquo;", "'");
	EscapeCode(str, "&lsquo;", "'");
	EscapeCode(str, "&ldquo;", "\"");
	EscapeCode(str, "&rdquo;", "\"");
	EscapeCode(str, "&quot;", "\"");
	EscapeCode(str, "&mdash;", "—");
	EscapeCode(str, "&hellip;", "……");
	EscapeCode(str, "&lt;", "<");
	EscapeCode(str, "&rarr;", "→");
	EscapeCode(str, "&cap;", "∩");

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
