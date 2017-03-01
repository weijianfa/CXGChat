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

class ChatManager: ChatRoom::IChatRoomObserver {
    
public:
    
    std::string token;
    
    ChatManager(const char *ip, int port);
    ~ChatManager();
    
    void Enter();
    
    virtual void __attribute__((__stdcall__)) OnChatRoom(ChatRoom::ChatRoomMsg crMsg, const char* szMsg);
    
    
    
    void setUser(long uid, long rid,const char *token);
private:
    ChatRoom::ChatRoomInfo m_RoomInfo;
    ChatRoom::IChatRoom*  m_pChatRoom;
};

#endif /* ChatManager_hpp */
