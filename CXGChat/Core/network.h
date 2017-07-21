#ifndef __NET_WORK_H_
#define __NET_WORK_H_

#include "Includes/PrecompileConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#define NETWORK_API __declspec(dllexport)
#endif

#define RECV_BUF_SIZE	4096 * 2
#define SEND_BUF_SIZE	2048

#define	HEAD_SIZE		4
#define	MAX_BUF_SIZE	8192 * 2

namespace NetWork
{
	class INetPeer;
	class INetPeerSink;

	typedef enum
	{
		use_type_server = 1,
		use_type_peer   = 2
	} use_type;

	typedef enum
	{
		err_udp            = 100,
		err_tcp_disconnect = 101,
		err_fatal          = 102,
	} media_err;
    
    enum ERRNO
    {
        CON_NETNOTREACH = 100001,
        CON_DISONCECONN,
        CON_SELECTERROR,
        CON_READDAERROR,
        CON_WRITEDERROR,
        CON_NOHEARTPACK,
        CON_ERRCREATESC,
        CON_STARTTHREAD,
    };
    
    class INetPeer
	{
	public:
		typedef enum
		{
			trans_tcp       = 1,
			trans_udp       = 2,
		} trans_type;

		typedef struct _PEER_CONFIG
		{
			char               sRemoteIP[32];
			unsigned short     nRemotePort;

			trans_type         transType;
			INetPeerSink*      pSink;

			void PEER_CONFIG()
			{
				memset(sRemoteIP, 0, sizeof(sRemoteIP));
				nRemotePort = 0;

				transType = trans_tcp;
				pSink = NULL;
			}
		} PEER_CONFIG;

	public:

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		virtual long __stdcall AddRef() = 0;
		virtual long __stdcall Release() = 0;

		virtual void __stdcall GetConfig(PEER_CONFIG& config) = 0;
		virtual void __stdcall UpdateConfig(const PEER_CONFIG& config) = 0;
		virtual bool __stdcall Connect() = 0;
		virtual bool __stdcall Open() = 0;
		virtual void __stdcall Close() = 0;
		virtual bool __stdcall SendData(const char* pData, int nLen) = 0;
	#else

		virtual long AddRef() = 0;
		virtual long Release() = 0;

		virtual void GetConfig(PEER_CONFIG& config) = 0;
		virtual void UpdateConfig(const PEER_CONFIG& config) = 0;
		virtual bool Connect() = 0;
		virtual bool Open() = 0;
		virtual void Close() = 0;
		virtual bool SendData(const char* pData, int nLen) = 0;
	#endif
	};

	class INetPeerSink
	{
	public:

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

		virtual void __stdcall OnRecvData(char* pData, long nLen) = 0;
		virtual void __stdcall OnSendOver() = 0;
		virtual void __stdcall OnNetErr(long nErr) = 0;
		virtual void __stdcall OnConnect(bool bSuc) = 0;
	#else

		virtual void OnRecvData(char* pData, long nLen) = 0;
		virtual void OnSendOver() = 0;
		virtual void OnNetErr(long nErr) = 0;
		virtual void OnConnect(bool bSuc) = 0;
	#endif
	};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	extern "C"
	{
		NETWORK_API INetPeer* CreateNetPeer(INetPeerSink* pNb);
		NETWORK_API void DeleteNetPeer(INetPeer* pNet);
	}
#else

	extern "C"
	{
		INetPeer* CreateNetPeer(INetPeerSink* pNb);
		void DeleteNetPeer(INetPeer* pNet);
	}
#endif
}

#endif /*__NET_WORK_H_*/
