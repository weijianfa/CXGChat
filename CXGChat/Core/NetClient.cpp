#include "NetClient.h"

#define BUF_SIZE 2048

CNetPeer::CNetPeer(INetPeerSink* pNb)
{
	m_RawLink = pNb;

	m_nRetCode = 0;
	m_nNeedCopySize = 0;
	m_nRefCount = 1;

	m_bRet = false;
	m_bThreadRet = false;
	m_bSendRet = false;

	memset(m_cLastRecv, 0, RECV_BUF_SIZE);
	m_Mutex = PTHREAD_MUTEX_INITIALIZER;
}

CNetPeer::~CNetPeer()
{
}

void CNetPeer::GetConfig(PEER_CONFIG& config)
{
	config = m_NetConfig;
}

void CNetPeer::UpdateConfig(const PEER_CONFIG& config)
{
	m_NetConfig = config;
}

bool CNetPeer::Connect()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	WSAData wsaData;

	m_nRetCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (m_nRetCode != NO_ERROR)
		return m_nRetCode;
#endif

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket < 0)
	{
        m_nRetCode = CON_ERRCREATESC;
		#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			WSACleanup();
		#endif
		return m_bRet;
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(m_NetConfig.nRemotePort);
	servAddr.sin_addr.s_addr = inet_addr(m_NetConfig.sRemoteIP);
#else

	struct sockaddr_in servAddr;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(m_NetConfig.nRemotePort);
	inet_pton(AF_INET, m_NetConfig.sRemoteIP, &servAddr.sin_addr);
#endif

	m_nRetCode = connect(m_socket, (struct sockaddr*)&servAddr, sizeof(servAddr));

	if (m_nRetCode < 0)
	{
        m_nRetCode = CON_NETNOTREACH;
		#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			WSAGetLastError();
		#else
			//geterror();
		#endif

		return m_bRet;
	}
	else
	{
		m_bRet = true;
		m_RawLink->OnConnect(m_bRet);
	}

	return m_bRet;
}

bool CNetPeer::Open()
{
    m_isdisconnect = false;
    
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    
    int nRet = pthread_create(&m_Connect, &attr, CNetPeer::ConnectBengin, this);
	if (!nRet)
		m_bThreadRet = true;
	else
        m_nRetCode = CON_STARTTHREAD;
		m_bThreadRet = false;

    pthread_attr_destroy (&attr);
	return m_bThreadRet;
}

// close the socket, this step should tell the upfloor
void CNetPeer::Close()
{
    if(!m_isdisconnect) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        closesocket(m_socket);
        WSACleanup();
#else
        close(m_socket);
#endif
        m_isdisconnect = true;
    }
    
    pthread_detach(m_Connect);
}

int CNetPeer::GetPacketHeadLenth(char* sData)
{
	int nPacketSize = 0;
	char* pPacketSize = (char*)&nPacketSize;
	memcpy(pPacketSize, sData, HEAD_SIZE);
	nPacketSize = ntohl(nPacketSize);

	if (nPacketSize > RECV_BUF_SIZE)
	{
		m_RawLink->OnNetErr(nPacketSize);
		Close();
	}

	return nPacketSize;
}

bool CNetPeer::SendData(const char* pData, int nLen)
{
    long ret = 0;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	ret = send(m_socket, pData, nLen, 0);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ret = send(m_socket, pData, nLen, SO_NOSIGPIPE);
#else 
    ret = send(m_socket, pData, nLen, MSG_NOSIGNAL);
#endif

    if (ret < 0) {
        m_nRetCode = CON_WRITEDERROR;
		m_bSendRet = false;
    }
	else
		m_bSendRet = true;

	return m_bSendRet;
}

bool CNetPeer::RecvData(char* pData, int nLen)
{
	int	nPacketSize, nValidSize, nLeftSize;
	nPacketSize = nValidSize = nLeftSize = 0;
	char cTempData[MAX_BUF_SIZE] = "";

	if (m_nNeedCopySize)
	{
		memcpy(cTempData, m_cLastRecv, m_nNeedCopySize);
		memset(m_cLastRecv, 0, RECV_BUF_SIZE);
	}
	for (int n = 0; n < nLen; n++)
	{
		cTempData[n + m_nNeedCopySize] = pData[n];
	}
	nLen = nLen + m_nNeedCopySize;
	m_nNeedCopySize = 0;

	if (nLen < HEAD_SIZE)
	{
		m_nNeedCopySize = nLen;
		for (int n = 0; n < nLen; n++)
		{
			m_cLastRecv[n] = cTempData[n];
		}
		return true;
	}
	
	nPacketSize = GetPacketHeadLenth(cTempData);
	nLeftSize = nLen - nPacketSize;

	while (nLeftSize > HEAD_SIZE)
	{
		nValidSize += nPacketSize;
		char cData[RECV_BUF_SIZE] = "";
		for (int n = 0; n < nLeftSize; n++)
		{
			cData[n] = cTempData[n + nValidSize];
		}
		nPacketSize = GetPacketHeadLenth(cData);
		nLeftSize -= nPacketSize;
	}

	if (!nLeftSize)
	{
		m_RawLink->OnRecvData(cTempData, nLen);
		return true;
	}

	char cBufData[MAX_BUF_SIZE] = "";
	memcpy(cBufData, cTempData, nValidSize);
	m_RawLink->OnRecvData(cBufData, nValidSize);

	m_nNeedCopySize = nLen - nValidSize;
	for (int n = 0; n < m_nNeedCopySize; n++)
	{
		m_cLastRecv[n] = cTempData[n + nValidSize];
	}

	return true;
}

long CNetPeer::AddRef()
{
	long nRef = 0;

	pthread_mutex_lock(&m_Mutex);

	m_nRefCount++;
	nRef = m_nRefCount;

	pthread_mutex_unlock(&m_Mutex);

	return nRef;
}

long CNetPeer::Release()
{
	long nRef = 0;

	pthread_mutex_lock(&m_Mutex);

	m_nRefCount--;
	nRef = m_nRefCount;

	pthread_mutex_unlock(&m_Mutex);

	if (!nRef){ delete this; }
	return nRef;
}


// this is a thread to call this function.
void* CNetPeer::ConnectBengin(void *arg)
{
	CNetPeer* pNp = (CNetPeer*)arg;

	bool bRet = false;
	char buf[SEND_BUF_SIZE] = "";
	char Recvbuf[RECV_BUF_SIZE] = "";
	
	fd_set  wFds, rFds, eFds;
	timeval tvTimeval;
	tvTimeval.tv_sec = 0;
	tvTimeval.tv_usec = 100;
    
    
    time_t tStamp;
    time(&tStamp);
    
    long count=0;

	while (true)
	{
		FD_ZERO(&wFds);
		FD_ZERO(&rFds);
		FD_ZERO(&eFds);

		FD_SET(pNp->m_socket, &wFds);
		FD_SET(pNp->m_socket, &rFds);
		FD_SET(pNp->m_socket, &eFds);
    
		usleep(900*1000);
        
        if(pNp->m_isdisconnect) {
            printf("chatroom: socket disconnected\n");
            break;
        }
        
        // to check fresh the client, 45s is to allowed.
        if(count == 10) {
            time_t tNow;
            time(&tNow);
            long tGapTime = (tNow - tStamp);
            //printf("@@@@%ld", tGapTime);
            if(tGapTime > 50 && tGapTime < 60) { // send the heartbeat you know.
                std::string jsonEnter = "{\"randomNumber\":\"222\",\"v\":\"0\"}";
                CPacket* pPacket = CPacket::CreateFromPayload((char*)jsonEnter.c_str(), (int)jsonEnter.length());
                pPacket->SetPacketType(0);
                pPacket->SetPacketAction(3);
                pNp->SendData(pPacket->GetTotal(), pPacket->GetTotalSize()) ;
                time(&tStamp);
            }
            if(tGapTime > 90)
            {
                pNp->m_nRetCode = CON_NOHEARTPACK;
                // exceeded time, this shoule be to close the socket and to notice the owner
                printf("chatroom: the client has exceeded time, you should connect agadin!\n");
				pNp->m_RawLink->OnNetErr(0);
                pNp->Close();
                break;
            }
            count = 0;
        }
        count++;

        // select the socket
		int nRet = select(FD_SETSIZE, &rFds, &wFds, &eFds, &tvTimeval);
		if (nRet > 0)             // have to process
		{
			if (FD_ISSET(pNp->m_socket, &rFds) > 0) 
			{
                
				int nRecvSize = recv(pNp->m_socket, Recvbuf, RECV_BUF_SIZE, 0);
				if (nRecvSize <= 0)
				{
                    pNp->m_nRetCode = CON_READDAERROR;
					pNp->m_RawLink->OnNetErr(pNp->m_nRetCode);
					pNp->Close();
					break;
				}
				pNp->RecvData(Recvbuf, nRecvSize);
			}

			if (FD_ISSET(pNp->m_socket, &wFds) > 0)  
			{
                
                bRet = pNp->SendData(buf, strlen(buf));
                if (!bRet)
                {
                    pNp->m_nRetCode = CON_WRITEDERROR;
                    printf("chatroom: SendData error!");
					pNp->m_RawLink->OnNetErr(pNp->m_nRetCode);
                    pNp->Close();
                    break;
                }
			}

			if (FD_ISSET(pNp->m_socket, &eFds) > 0)
            {
                // some errors.
                printf("chatroom: SelectData error!\n");
                pNp->m_nRetCode = CON_SELECTERROR;
				pNp->m_RawLink->OnNetErr(pNp->m_nRetCode);
                pNp->Close();
                break;
            }
		} else if(nRet == 0) {  // socket close
            pNp->m_nRetCode = CON_DISONCECONN;
	    	pNp->m_RawLink->OnNetErr(pNp->m_nRetCode);
            pNp->Close();
            printf("chatroom: SendData error1!\n");
            break;
        } else {                // error other
            pNp->m_nRetCode = CON_ERRCREATESC;
	   		pNp->m_RawLink->OnNetErr(pNp->m_nRetCode);
            //pNp->Close();
            printf("chatroom: SendData error2!\n");
			break;
        }
	}

	return 0;
}
