//
//  ChatManager.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/22.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "ChatManager.hpp"

ChatManager::~ChatManager() {
    
}

void ChatManager::Enter() {
    
    if(!m_pChatRoom)
        m_pChatRoom = CreateChatRoom(this);
    
    m_pChatRoom->SetToken(token);
    
    
    m_pChatRoom->SetChatRoomInfo(m_RoomInfo);
    
    int nRet = 0;
    if(!m_pChatRoom->IsEntered())
    {
        nRet = m_pChatRoom->EnterChatRoom();
    }
}

ChatManager::ChatManager(const char *ip, int port) {
    m_RoomInfo.strIp[0] = *ip;
    m_RoomInfo.strIp[1] = *ip;
    m_RoomInfo.strIp[2] = *ip;
    
    m_RoomInfo.nPort = port;

}

void ChatManager::setUser(long uid, long rid,const char *token) {
    
    m_RoomInfo.nMasterId = uid;
    m_RoomInfo.nRoomId = rid;
    this->token = *token;
    
}



void ChatManager::OnChatRoom(ChatRoom::ChatRoomMsg crMsg, const char *szMsg) {
    printf("OnChatRoom ChatRoomMsg= %d  \n",crMsg);
    printf("OnChatRoom massage = %s  \n",szMsg);
    ChatRoom::ChatRoomMsg msg = crMsg;
    std::string aMsg = szMsg;
};
