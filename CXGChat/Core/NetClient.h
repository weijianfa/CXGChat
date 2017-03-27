#ifndef __NET_CLIENT_H_
#define __NET_CLIENT_H_

#include "network.h"
#include "Packet.h"

using namespace NetWork;

enum ERRNO {
    CON_NETNOTREACH = 100001,
    CON_DISONCECONN,
    CON_SELECTERROR,
    CON_READDAERROR,
    CON_WRITEDERROR,
    CON_NOHEARTPACK,
    CON_ERRCREATESC,
    CON_STARTTHREAD,
};

class CNetPeer
	: public INetPeer
{
public:
	CNetPeer(INetPeerSink* pNb);
	~CNetPeer();

public:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	virtual long __stdcall AddRef();
	virtual long __stdcall Release();

	virtual void __stdcall GetConfig(PEER_CONFIG& config);
	virtual void __stdcall UpdateConfig(const PEER_CONFIG& config);
	virtual bool __stdcall SendData(const char* pData, int nLen);
	virtual bool __stdcall RecvData(char* pData, int nLen);

	virtual bool __stdcall Connect();
	virtual bool __stdcall Open();
	virtual void __stdcall Close();
#else

	virtual long __attribute__((__stdcall__)) AddRef();
	virtual long __attribute__((__stdcall__)) Release();

	virtual void __attribute__((__stdcall__)) GetConfig(PEER_CONFIG& config);
	virtual void __attribute__((__stdcall__)) UpdateConfig(const PEER_CONFIG& config);
	virtual bool __attribute__((__stdcall__)) SendData(const char* pData, int nLen);
	virtual bool __attribute__((__stdcall__)) RecvData(char* pData, int nLen);

	virtual bool __attribute__((__stdcall__)) Connect();
	virtual bool __attribute__((__stdcall__)) Open();
	virtual void __attribute__((__stdcall__)) Close();
#endif

private:

	static void* ConnectBengin(void *arg);
	void ConnectEnd();

	int GetPacketHeadLenth(char* pData);

private:

	int	m_nRetCode;
	int	m_nNeedCopySize;
	
	bool	m_bRet;
	bool	m_bThreadRet;
	bool	m_bSendRet;

	long    m_nRefCount;
	char	m_cLastRecv[RECV_BUF_SIZE];

	PEER_CONFIG	m_NetConfig;
	INetPeerSink*	m_RawLink;

	pthread_t	m_Connect;
	pthread_mutex_t	m_Mutex;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SOCKET		m_socket;
#else
	int		m_socket;
#endif
};

#endif
