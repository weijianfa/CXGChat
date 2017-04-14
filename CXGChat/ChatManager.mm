//
//  ChatManager.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/22.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "ChatManager.hpp"

Message* getMessage(PtlBase* ptl) {
    Message* message = [[Message alloc] init];
    [message setUid: [NSString stringWithUTF8String:ptl->getUserID().c_str()]];
    [message setMsg: [NSString stringWithUTF8String:ptl->getMsg().c_str()]];
    [message setNickName: [NSString stringWithUTF8String:ptl->getNickName().c_str()]];
    [message setType:ptl->type];
    
    
    switch(ptl->type) {
        case 1: // usermsg，feiping，broadcast
        case 2: // gift
        case 4: // enter in
            [[message getUser] setFensi:ptl->fensi];
            [[message getUser] setCaifu:ptl->caifu];
            [[message getUser] setJuese:ptl->juese];
            break;
        case 3: // sys
            break;
    }
    
    switch(ptl->type) {
        case 1: // usermsg，feiping，broadcast
            break;
        case 2: // gift
        case 4: // enter in
            [[message getGift] setName:[NSString stringWithUTF8String:ptl->giftName.c_str()]];
            [[message getGift] setCount:ptl->giftCount];
            [[message getGift] setIsShow:ptl->isShowGift];
            [[message getGift] setVersion:ptl->giftVersion];
            [[message getGift] setGiftId:ptl->giftid];
            [[message getGift] setZipPath:[NSString stringWithUTF8String:ptl->zipPath.c_str()]];
            break;
        case 3: // sys
            break;
    }
    
    return message;
}

ChatManager * ChatManager::m_pInstance;

ChatManager::ChatManager() {
    
}

ChatManager::~ChatManager() {
    
}

void ChatManager::Enter() {
    
    if(!m_pChatRoom)
        m_pChatRoom = CreateChatRoom(this);
    
   
    
    m_pChatRoom->SetChatRoomInfo(m_RoomInfo);
    
    m_pChatRoom->SetToken(token);
    
    long nRet = 0;
    if(!m_pChatRoom->IsEntered())
    {
        nRet = m_pChatRoom->EnterChatRoom();
    }
}

void ChatManager::Speak(const char *message, const char *uid, bool isall) {
    if(m_pChatRoom->IsEntered()) {
        m_pChatRoom->Speak(message, uid, isall);
    }
}

void ChatManager::ExitChatRoom() {
    m_pChatRoom->ExitChatRoom();
}

void ChatManager::setHost(const char *ip, long port) {
    m_RoomInfo.strIp[0] = ip;
    m_RoomInfo.strIp[1] = ip;
    m_RoomInfo.strIp[2] = ip;
    
    m_RoomInfo.nPort = port;

}

void ChatManager::setUser(const char *uid, const char *rid,const char *token) {
    m_RoomInfo.nMasterId = uid;
    m_RoomInfo.nRoomId = rid;
    this->token = token;
    
}

void ChatManager::OnMsg(PtlBase* ptl) {
    printf("OnMsg ChatRoomMsg= %s  \n", ptl->getDisplayMsg().c_str());
    if(mController) {
        [mController doOnMessage: getMessage(ptl)];
    }
}

void ChatManager::OnError(long errcode, char* msg) {
    printf("OnMsg OnError= (%ld)%s  \n", errcode, msg);
    if(mController) {
        [mController doOnError:errcode Msg:[NSString stringWithUTF8String:msg]];
    }
}

void ChatManager::setController(ChatControl* listener) {
    this->mController = listener;
}

ChatManager *ChatManager::GetInstance() {
    if(m_pInstance == NULL)  //判断是否第一次调用
        m_pInstance = new ChatManager();
    return m_pInstance;
}




