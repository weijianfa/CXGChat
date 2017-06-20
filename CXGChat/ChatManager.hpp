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
#import  "MessageControl.h"


class ChatManager: ChatRoom::IChatRoomObserver
{
public:
    ChatManager();
    ~ChatManager();
    
    static ChatManager *GetInstance();
    
    virtual void OnMsg(PtlBase* ptl);
    virtual void OnError(int errcode, char* msg);
    
    void setHost(const char *ip, long port);
    void setUser(const char *uid,const char *rid);
    void setToken(const char *token);
    void setController(ChatControl* listener);
    
    void EnterChatRoom();
    void ExitChatRoom();
    
    void SendChatMsg(const char *message, const char *uid ,bool isprivate);
    void RequestUserInfo(const char *uid, long version);
    void RequestUserList(long pageNo, long maxNum, long version);
    void UserList();
    
private:
    
    Message* setUserInfo(Message* message, PtlBase* ptl);
    Message* setReceiveUserInfo(Message* message, PtlBase* ptl);
    Message* setGiftInfo(Message* message, PtlBase* ptl);
    Message* setUserList(Message* message, PtlBase* ptl);
   
private:
    
    static ChatManager* m_pInstance;
    
    std::string m_strToken;
    ChatControl* m_pController;
    
    ChatRoom::ChatRoomInfo m_RoomInfo;
    ChatRoom::IChatRoom*  m_pChatRoom;
    
};

#endif /* ChatManager_hpp */
