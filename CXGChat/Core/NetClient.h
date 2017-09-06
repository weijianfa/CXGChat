#ifndef __NET_CLIENT_H_
#define __NET_CLIENT_H_

#include "network.h"

using namespace NetWork;

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

	virtual long AddRef();
	virtual long Release();

	virtual void GetConfig(PEER_CONFIG& config);
	virtual void UpdateConfig(const PEER_CONFIG& config);
	virtual bool SendData(const char* pData, int nLen);
	virtual bool RecvData(char* pData, int nLen);

	virtual bool Connect();
	virtual bool Open();
	virtual void Close();
#endif

private:

	static void* ConnectBengin(void *arg);
	void ConnectEnd();

	int GetPacketHeadLenth(char* pData);

private:

	int	m_nRetCode;
	int	m_nNeedCopySize;
	
	bool	m_bRet;
	volatile bool	m_bOnLoop;

	long    m_nRefCount;
	char	m_cLastRecv[RECV_BUF_SIZE];

	PEER_CONFIG	m_NetConfig;
	INetPeerSink*	m_RawLink;

	pthread_t	m_Connect;
	pthread_mutex_t	m_Mutex;
    pthread_mutex_t	m_tMutex;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SOCKET		m_socket;
#else
	int		m_socket;
#endif
};

#endif
