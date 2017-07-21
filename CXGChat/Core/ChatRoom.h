// ChatRoom.h
//

#ifndef __CHAT_ROOM_H_
#define __CHAT_ROOM_H_

#include "cxgChatRoom.h"
#include "RawLink.h"
#include "PtlBase.hpp"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Timer.h"
#endif

using namespace ChatRoom;

static CRawLink*	g_pLink = NULL;

class CChatRoom
	: public IChatRoom
	, public ILinkSink
	, public CRefCount
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	, public CTimer
#endif
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
	virtual void __stdcall SendChatMsg(std::string strMsg, unsigned long long nMasterid, bool bPrivate);

	virtual std::string __stdcall GetErrMsg(void);
	virtual void __stdcall SendChatMsgPacket();
	virtual void __stdcall SendHreatBeatPacket();
#else

	virtual bool IsEntered(void);
	virtual bool IsConnect(void);

	virtual long EnterChatRoom(void);
	virtual long ReentryChatRoom(int nNodeNum = 0);
    //virtual long Speak(std::string words, std::string uid, bool ispublic);
    virtual void UserList(void);
	virtual void ExitChatRoom(void);

	virtual void SetToken(std::string strToken);
	virtual void SetChatRoomInfo(ChatRoomInfo RoomInfo);
    virtual void SendChatMsg(std::string strMsg,std::string strMasterid, bool bPrivate);
    virtual void RequestUserInfo(std::string strUid,long nVersion);
    virtual void RequestUserList(long nOageNo,long nMax, long nType, long nVersion);
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

	virtual long AddRef();
	virtual long Release();
	virtual void OnLinkPacket(CRawLink* pLink, CPacket* pPacket);
	virtual void OnLinkErr(CRawLink* pLink);

    void KeepLive();
    bool IsEnterChatRoom(time_t current);
    static void* SendHeartBeat(void *arg);
    
#endif

	void OpenTCPLink(int nNodeNum);

	std::string EscapeCode(std::string& str);
	bool EscapeCode(std::string& str, std::string oldchar, std::string newchar);

	std::string Utf_8ToANSI(const std::string& strUtf8);
	std::string ANSIToUtf_8(const std::string& strANSI);
	bool Utf_8ToANSI(const char* pUtf8, int nUtf_8Len, char* pANSI, int* ANSILen);
	bool ANSIToUtf_8(const char* pANSI, int nANSILen, char* pUtf_8, int* Utf_8Len);

private:

	bool m_bEnter;
	bool m_bConnect;

    std::string m_nMasterId;
    std::string m_nRoomId;
    std::string m_nMasterNo;
	unsigned int       m_nKeepLiveTimer;

	ChatRoomMsg	m_eMsgType;
	char*	m_strChatMsg;
    
    int         m_nRoomPort;
	std::string	m_strToken;
	std::string	m_strRoomIp[MAX_CHAT_NODE];

	pthread_mutex_t    m_SynchMutex;
    IChatRoomObserver* m_pObserver;
    CRawLink*          m_pLink;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HANDLE      m_hEnter;
#else
    time_t      m_tLastTime;
    time_t      m_tEvent;
    pthread_t   m_HeartBeat;
#endif
};

#endif
