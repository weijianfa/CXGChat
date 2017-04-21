// ChatRoom.h
//

#ifndef __CHAT_ROOM_H_
#define __CHAT_ROOM_H_

#include "cxgChatRoom.h"
#include "RawLink.h"
#include "Timer.h"
#include "PtlBase.hpp"

std::string unescape(char* str);

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

	virtual long  __stdcall EnterChatRoom(void);
	virtual long  __stdcall ReentryChatRoom(int nNodeNum =0);
	virtual void __stdcall ExitChatRoom(void);

	virtual void __stdcall SetToken(std::string strToken);
	virtual void __stdcall SetChatRoomInfo(ChatRoomInfo RoomInfo);

	virtual std::string __stdcall GetErrMsg(void);
#else

	virtual bool IsEntered(void);
	virtual bool IsConnect(void);

	virtual long EnterChatRoom(void);
	virtual long ReentryChatRoom(long nNodeNum = 0);
    virtual long Speak(std::string words, std::string uid, bool ispublic);
    virtual void UserList(void);
	virtual void ExitChatRoom(void);

	virtual void SetToken(std::string strToken);
	virtual void SetChatRoomInfo(ChatRoomInfo RoomInfo);

	virtual std::string GetErrMsg(void);
#endif

private:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	virtual long __stdcall AddRef();
	virtual long __stdcall Release();
	virtual void __stdcall OnLinkPacket(CRawLink* pLink, CPacket* pPacket);
	virtual void __stdcall OnLinkErr(CRawLink* pLink);

	bool OnTimer(int nTimeId);
#else

	virtual long __attribute__((__stdcall__))  AddRef();
	virtual long __attribute__((__stdcall__))  Release();
	virtual void __attribute__((__stdcall__))  OnLinkPacket(CRawLink* pLink, CPacket* pPacket);
	virtual void __attribute__((__stdcall__))  OnLinkErr(CRawLink* pLink);

	static void __attribute__((__stdcall__))  OnTimer(long nTimeId);
#endif

	void OpenTCPLink(long nNodeNum);

	std::string TransCode(const std::string& strUtf8);
	std::string EscapeCode(std::string& str);
	bool EscapeCode(std::string& str, std::string oldchar, std::string newchar);
	bool Utf_8ToANSI(const char* pUtf8, int nUtf_8Len, char* pANSI, int* ANSILen);

private:

	bool m_bEnter;
	bool m_bConnect;

	std::string m_nMasterId;
	std::string m_nRoomId;
	unsigned int   m_nKeepLiveTimer;

	long		m_nRoomPort;
    long        lastPackTime = 0;
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
