//
//  ChatManager.hpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/22.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#ifndef ChatManager_hpp
#define ChatManager_hpp

#include "cxgChatRoom.h"
#include "CXGChat.h"

#import  "MessageControl.h"


class ChatManager: ChatRoom::IChatRoomObserver
{
private:
    ChatManager();   //构造函数是私有的

    static ChatManager *m_pInstance;
public:
    static ChatManager *GetInstance();
    
    
public:
    
    std::string token;
    ~ChatManager();
    
    virtual void OnMsg(PtlBase* ptl);
    virtual void OnError(int errcode, char* msg);
    
    void setHost(const char *ip, long port);
    void setUser(const char *uid,const char *rid,const char *token);
    void setController(ChatControl* listener);
    
    void Enter();
    void SendChatMsg(const char *message, const char *uid ,bool isprivate);
    void UserList();
    
    void ExitChatRoom();
private:
    ChatRoom::ChatRoomInfo m_RoomInfo;
    ChatRoom::IChatRoom*  m_pChatRoom = 0;
    ChatControl* mController;
};

#endif /* ChatManager_hpp */
