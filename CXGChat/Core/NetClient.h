#ifndef __NET_CLIENT_H_
#define __NET_CLIENT_H_

#include "network.h"
#include "Packet.h"

#define RECV_BUF_SIZE 8192
#define SEND_BUF_SIZE 2048
#define	HEAD_SIZE	4

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
	virtual bool __stdcall RecvData();

	virtual bool __stdcall Connect();
	virtual bool __stdcall Open();
	virtual void __stdcall Close();
#else

	virtual long __attribute__((__stdcall__)) AddRef();
	virtual long __attribute__((__stdcall__)) Release();

	virtual void __attribute__((__stdcall__)) GetConfig(PEER_CONFIG& config);
	virtual void __attribute__((__stdcall__)) UpdateConfig(const PEER_CONFIG& config);
	virtual bool __attribute__((__stdcall__)) SendData(const char* pData, int nLen);
	virtual bool __attribute__((__stdcall__)) RecvData();

	virtual bool __attribute__((__stdcall__)) Connect();
	virtual bool __attribute__((__stdcall__)) Open();
	virtual void __attribute__((__stdcall__)) Close();
#endif

private:

	static void* ConnectBengin(void *arg);
	void ConnectEnd();

private:

	int		m_nRetCode;
	int		m_nRecvSize;
	int		m_nPacketSize;
	
	bool	m_bRet;
	bool	m_bThreadRet;
	bool	m_bSendRet;
	bool	m_bReading;

	long    m_nRefCount;
	char	m_cHeadBuf[HEAD_SIZE];
	char	m_cFullBuf[RECV_BUF_SIZE];

	PEER_CONFIG		m_NetConfig;
	INetPeerSink*	m_RawLink;

	pthread_t		m_Connect;
	pthread_mutex_t	m_Mutex;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SOCKET			m_socket;
#else
	int				m_socket;
#endif
};

#endif
