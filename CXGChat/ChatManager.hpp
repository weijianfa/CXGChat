//
//  ChatManager.hpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/22.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#ifndef ChatManager_hpp
#define ChatManager_hpp

#include <stdio.h>
#include "cxgChatRoom.h"
#include "CXGChat.h"

class ChatManager: ChatRoom::IChatRoomObserver {
    
public:
    
    std::string token;
    
    ChatManager(const char *ip, int port);
    ~ChatManager();
    
    void Enter();
    
    virtual void __attribute__((__stdcall__)) OnMsg(PtlBase* ptl);
    
    virtual void __attribute__((__stdcall__)) OnError(int errcode, char* msg);
    
    
    void setUser(const char *uid,const char *rid,const char *token);
    void setListner(MsgListener* listener);
private:
    ChatRoom::ChatRoomInfo m_RoomInfo;
    ChatRoom::IChatRoom*  m_pChatRoom = 0;
    MsgListener* listener;
};

#endif /* ChatManager_hpp */
