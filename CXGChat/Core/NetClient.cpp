#include "NetClient.h"

#define BUF_SIZE 2048

CNetPeer::CNetPeer(INetPeerSink* pNb)
{
	m_RawLink = pNb;

	m_nRetCode = 0;
	m_nRefCount = 1;
	m_bRet = false;
	m_bThreadRet = false;
	m_bSendRet = false;

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
	int nRet = pthread_create(&m_Connect, NULL, CNetPeer::ConnectBengin, this);
	if (!nRet)
		m_bThreadRet = true;
	else
		m_bThreadRet = false;

	return m_bThreadRet;
}

void CNetPeer::Close()
{

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	closesocket(m_socket);
	WSACleanup();
#else
	close(m_socket);
#endif
}

bool CNetPeer::SendData(const char* pData, int nLen)
{

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_nRetCode = send(m_socket, pData, nLen, 0);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	m_nRetCode = send(m_socket, pData, nLen, SO_NOSIGPIPE);
#else 
    m_nRetCode = send(m_socket, pData, nLen, MSG_NOSIGNAL);
#endif

	if (m_nRetCode < 0)
		m_bSendRet = false;
	else
		m_bSendRet = true;

	return m_bSendRet;
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

void* CNetPeer::ConnectBengin(void *arg)
{
	CNetPeer* pNp = (CNetPeer*)arg;

	long  nCount = -1;
	bool bRet = false;
	char buf[BUF_SIZE];
	char bufRecv[BUF_SIZE];
	
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
        
        usleep(1000);// tick 中添加sleep，降低cpu损耗。
        
        if(count == 20) {
            time_t tNow;
            time(&tNow);
            if(tNow - tStamp > 30)
            {
                // exceeded time, this shoule be to close the socket and to notice the owner
                printf("the client has exceeded time, you should connect agadin! %ld,%ld\n",tNow ,tStamp);
            }
            count = 0;
        }
        count++;

		int nRet = select(FD_SETSIZE, &rFds, &wFds, &eFds, &tvTimeval);
		if (nRet > 0)             // have to process
		{
			if (FD_ISSET(pNp->m_socket, &rFds) > 0) 
			{
                time(&tStamp);  // reset the time to show data comes;
				nCount = recv(pNp->m_socket, bufRecv, BUF_SIZE, 0);
//                printf("qqqqq  %d, %s\n", nCount, bufRecv);
				pNp->m_RawLink->OnRecvData(bufRecv, nCount);
			}

			if (FD_ISSET(pNp->m_socket, &wFds) > 0)  
			{
                
				if (nCount > 0)
				{
					bRet = pNp->SendData(buf, strlen(buf));
					if (!bRet)
					{
                        printf("SendData error!");
						pNp->Close();
						break;
					}
					nCount = -1;
				}
			}

			if (FD_ISSET(pNp->m_socket, &eFds) > 0){ break; }
		} else if(nRet == 0) {  // socket close
            pNp->m_RawLink->OnNetErr(1001);
            printf("SendData error1!");
            break;
        } else {                // error other
            pNp->m_RawLink->OnNetErr(1002);
            printf("SendData error2!");
			break;
        }
	}

	return 0;
}
