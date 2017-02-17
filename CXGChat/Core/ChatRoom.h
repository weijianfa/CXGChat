// ChatRoom.h
//

#ifndef __CHAT_ROOM_H_
#define __CHAT_ROOM_H_

#include "cxgChatRoom.h"
#include "RawLink.h"
#include "Timer.h"

using namespace ChatRoom;

static CRawLink*	g_pLink = NULL;

class CChatRoom
	: public IChatRoom
	, public ILinkSink
	, public CRefCount
	, public CTimer

{
public:
	CChatRoom(IChatRoomObserver* pObserver);
	~CChatRoom();


public:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	virtual bool __stdcall IsEntered(void);
	virtual bool __stdcall IsConnect(void);

	virtual int  __stdcall EnterChatRoom(void);
	virtual int  __stdcall ReentryChatRoom(int nNodeNum =0);
	virtual void __stdcall ExitChatRoom(void);

	virtual void __stdcall SetToken(std::string strToken);
	virtual void __stdcall SetChatRoomInfo(ChatRoomInfo RoomInfo);

	virtual std::string __stdcall GetErrMsg(void);
#else

	virtual bool __attribute__((__stdcall__)) IsEntered(void);
	virtual bool __attribute__((__stdcall__)) IsConnect(void);

	virtual int  __attribute__((__stdcall__)) EnterChatRoom(void);
	virtual int  __attribute__((__stdcall__)) ReentryChatRoom(int nNodeNum = 0);
	virtual void __attribute__((__stdcall__)) ExitChatRoom(void);

	virtual void __attribute__((__stdcall__)) SetToken(std::string strToken);
	virtual void __attribute__((__stdcall__)) SetChatRoomInfo(ChatRoomInfo RoomInfo);

	virtual std::string __attribute__((__stdcall__)) GetErrMsg(void);
#endif

private:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	virtual long __stdcall AddRef();
	virtual long __stdcall Release();
	virtual void __stdcall OnLinkPacket(CRawLink* pLink, CPacket* pPacket);
	virtual void __stdcall OnLinkErr(CRawLink* pLink);

	bool OnTimer(int nTimeId);
#else

	virtual long __attribute__((__stdcall__)) AddRef();
	virtual long __attribute__((__stdcall__)) Release();
	virtual void __attribute__((__stdcall__)) OnLinkPacket(CRawLink* pLink, CPacket* pPacket);
	virtual void __attribute__((__stdcall__)) OnLinkErr(CRawLink* pLink);

	static void OnTimer(int nTimeId);
#endif

	void OpenTCPLink(int nNodeNum);

	std::string TransCode(const std::string& strUtf8);
	std::string EscapeCode(std::string& str);
	bool EscapeCode(std::string& str, std::string oldchar, std::string newchar);
	bool Utf_8ToANSI(const char* pUtf8, int nUtf_8Len, char* pANSI, int* ANSILen);

private:

	bool m_bEnter;
	bool m_bConnect;

	unsigned long long m_nMasterId;
	unsigned long long m_nRoomId;
	unsigned int   m_nKeepLiveTimer;

	int		m_nRoomPort;
	const char*	m_strChatMsg;
	ChatRoomMsg	m_eMsgType;
	std::string	m_strToken;
	std::string	m_strRoomIp[MAX_CHAT_NODE];

	IChatRoomObserver* m_pObserver;
	pthread_mutex_t    m_SynchMutex;

	CRawLink*	m_pLink;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HANDLE      m_hEnter;
#else
	sem_t		m_semEnter;
	struct timespec		m_tOutTime;
#endif
};

#endif
