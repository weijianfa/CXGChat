//
//  ChatManager.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/22.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "ChatManager.hpp"

ChatManager * ChatManager::m_pInstance;
ChatManager::ChatManager()
{
    m_strToken = "";
    m_pChatRoom = NULL;
    m_pInstance = NULL;
    
    m_pController = NULL;
}

ChatManager::~ChatManager()
{
    if(m_pChatRoom)
        DeleteChatRoom(m_pChatRoom);
    
    m_pInstance = NULL;
}

ChatManager *ChatManager::GetInstance()
{
    if(m_pInstance == NULL)
        m_pInstance = new ChatManager();
    
    return m_pInstance;
}

void ChatManager::EnterChatRoom()
{
    if(!m_pChatRoom)
        m_pChatRoom = CreateChatRoom(this);
    
    m_pChatRoom->SetChatRoomInfo(m_RoomInfo);
    m_pChatRoom->SetToken(m_strToken);
    
    if(!m_pChatRoom->IsEntered())
        m_pChatRoom->EnterChatRoom();
}

void ChatManager::SendChatMsg(const char *message, const char *uid, bool isprivate)
{
    m_pChatRoom->SendChatMsg(message, uid, isprivate);
}

void ChatManager::RequestUserInfo(const char *uid, long version)
{
    m_pChatRoom->RequestUserInfo(uid, version);
}

void ChatManager::RequestUserList(long pageNo, long maxNum, long version)
{
    m_pChatRoom->RequestUserList(pageNo, maxNum, version);
}

void ChatManager::UserList()
{
    m_pChatRoom->UserList();
}

void ChatManager::ExitChatRoom()
{
    if(m_pChatRoom->IsEntered())
        m_pChatRoom->ExitChatRoom();
}

void ChatManager::setHost(const char *ip, long port)
{
    m_RoomInfo.strIp[0] = ip;
    m_RoomInfo.strIp[1] = ip;
    m_RoomInfo.strIp[2] = ip;
    
    m_RoomInfo.nPort = port;
}

void ChatManager::setUser(const char *uid, const char *rid)
{
    m_RoomInfo.nMasterId = uid;
    m_RoomInfo.nRoomId = rid;
}

void ChatManager::setToken(const char* token)
{
    m_strToken = token;
}

void ChatManager::setController(ChatControl* listener)
{
    m_pController = listener;
}

void ChatManager::OnError(int errcode, std::string msg)
{
    if(m_pController)
        [m_pController doOnError:errcode Msg:[NSString stringWithUTF8String:msg.c_str()]];
}

void ChatManager::OnMsg(PtlBase* ptl)
{
    Message* message = [[Message alloc] init];
    [message setMsgBaseInfoWithType:ptl->m_nType andSubType:ptl->m_nSubType andContent:[NSString stringWithUTF8String:ptl->m_strMsg.c_str()]];
    [message setMsgExtraInfo:ptl->m_nExtraProperty];
    
    if(ptl->m_nType == 8)
        message = setUserList(message, ptl);
    else
    {
        message = setUserInfo(message, ptl);
        
        if(!ptl->m_ReceiveUser.userID.empty())
            message = setReceiveUserInfo(message, ptl);
        
        if(ptl->m_Gift.giftID)
            message = setGiftInfo(message, ptl);
    }
    
    if(m_pController)
        [m_pController doOnMessage: message];
}

Message* ChatManager::setUserInfo(Message* message, PtlBase* ptl)
{

    [[message getUser] setUserBaseInfoWithUid:[NSString stringWithUTF8String:ptl->m_User.userID.c_str()]
                                  andNickName:[NSString stringWithUTF8String:ptl->m_User.nickName.c_str()]
                                  andHeadIcon:[NSString stringWithUTF8String:ptl->m_User.headIcon.c_str()]
                                   andGameUid:[NSString stringWithUTF8String:ptl->m_User.gameUid.c_str()]];
    [[message getUser] setUserLevelInfoWithFans:ptl->m_User.fansLevel
                                        andRich:ptl->m_User.richLevel
                                        andUser:ptl->m_User.userLevel];
    [[message getUser] setUserDetailInfoWithRoomRole: [NSString stringWithUTF8String:ptl->m_User.roomRole.c_str()]
                                         andUserType: ptl->m_User.userType
                                           andRoleID: ptl->m_User.roleID
                                          andSortNum: ptl->m_User.sortNum];
    [[message getUser] setUserGameInfoWithGameZoneName: [NSString stringWithUTF8String:ptl->m_User.gameZoneName.c_str()]
                                         andEquipScore: ptl->m_User.equipScore
                                       andGameRoleType: ptl->m_User.gameRoleType
                                       andGameVipLevel:ptl->m_User.gameVIPLevel];
    [[[message getUser] getEntryAnimation] setProPertyWithID:ptl->m_User.AnimationID
                                                     andPath:[NSString stringWithUTF8String:ptl->m_User.AnimationPath.c_str()]
                                                  andVersion:[NSString stringWithUTF8String:ptl->m_User.AnimationVer.c_str()]
                                                      isShow:ptl->m_User.isAnimationShow];
    [[message getUser] setMedalInfoWith:ptl->m_User.medal];
    [[message getReceiveUser] setAnchorSpecialNoWith:[NSString stringWithUTF8String:ptl->m_User.specialNo.c_str()]];
    
    return message;
}

Message* ChatManager::setReceiveUserInfo(Message* message, PtlBase* ptl)
{
    
    [[message getReceiveUser] setUserBaseInfoWithUid:[NSString stringWithUTF8String:ptl->m_ReceiveUser.userID.c_str()]
                                         andNickName:[NSString stringWithUTF8String:ptl->m_ReceiveUser.nickName.c_str()]
                                         andHeadIcon:[NSString stringWithUTF8String:ptl->m_ReceiveUser.headIcon.c_str()]
                                          andGameUid:[NSString stringWithUTF8String:ptl->m_ReceiveUser.gameUid.c_str()]];
    [[message getReceiveUser] setUserLevelInfoWithFans:ptl->m_ReceiveUser.fansLevel
                                               andRich:ptl->m_ReceiveUser.richLevel
                                               andUser:ptl->m_ReceiveUser.userLevel];
    [[message getReceiveUser] setUserDetailInfoWithRoomRole: [NSString stringWithUTF8String:ptl->m_ReceiveUser.roomRole.c_str()]
                                                andUserType: ptl->m_ReceiveUser.userType
                                                  andRoleID: ptl->m_ReceiveUser.roleID
                                                 andSortNum: ptl->m_ReceiveUser.sortNum];
    [[message getReceiveUser] setUserGameInfoWithGameZoneName: [NSString stringWithUTF8String:ptl->m_ReceiveUser.gameZoneName.c_str()]
                                                andEquipScore: ptl->m_ReceiveUser.equipScore
                                              andGameRoleType: ptl->m_ReceiveUser.gameRoleType
                                              andGameVipLevel:ptl->m_ReceiveUser.gameVIPLevel];
    [[message getReceiveUser] setAnchorSpecialNoWith:[NSString stringWithUTF8String:ptl->m_ReceiveUser.specialNo.c_str()]];
    return message;
}

Message* ChatManager::setGiftInfo(Message* message, PtlBase* ptl)
{
    [[message getGift] setGiftBaseInfoWithName:[NSString stringWithUTF8String:ptl->m_Gift.name.c_str()]
                                         andID:ptl->m_Gift.giftID
                                       andIcon:[NSString stringWithUTF8String:ptl->m_Gift.icon.c_str()]];
    
    [[message getGift] setGiftDetailInfoWithUniqueID:[NSString stringWithUTF8String:ptl->m_Gift.uniqueID.c_str()]
                                            andCount:ptl->m_Gift.count
                                             andType:ptl->m_Gift.type
                                             andFree:ptl->m_Gift.isFree];
    
    [[message getGift] setGiftComboInfoWithAutoCombo:ptl->m_Gift.isAutoCombo
                                            andCombo:ptl->m_Gift.isCombo
                                         andComboNum:ptl->m_Gift.comboNum
                                         andGroupNum:ptl->m_Gift.comboGroupNum];
    
    [[message getGift] setGiftVersion:ptl->m_Gift.version];
    return message;
}

Message* ChatManager::setUserList(Message* message, PtlBase* ptl)
{
    while(!ptl->getUserFromList().userID.empty())
    {
        [[message getUser] setUserBaseInfoWithUid:[NSString stringWithUTF8String:ptl->getUserFromList().userID.c_str()]
                                      andNickName:[NSString stringWithUTF8String:ptl->getUserFromList().nickName.c_str()]
                                      andHeadIcon:[NSString stringWithUTF8String:ptl->getUserFromList().headIcon.c_str()]
                                       andGameUid:[NSString stringWithUTF8String:ptl->getUserFromList().gameUid.c_str()]];
        [[message getUser] setUserLevelInfoWithFans:ptl->getUserFromList().fansLevel
                                            andRich:ptl->getUserFromList().richLevel
                                            andUser:ptl->getUserFromList().userLevel];
        [[message getUser] setUserDetailInfoWithRoomRole: [NSString stringWithUTF8String:ptl->getUserFromList().roomRole.c_str()]
                                             andUserType:ptl->getUserFromList().userType
                                               andRoleID:ptl->getUserFromList().roleID
                                              andSortNum:ptl->getUserFromList().sortNum];
        [[message getUser] setUserGameInfoWithGameZoneName: [NSString stringWithUTF8String:ptl->getUserFromList().gameZoneName.c_str()]
                                             andEquipScore:ptl->getUserFromList().equipScore
                                           andGameRoleType:ptl->getUserFromList().gameRoleType
                                           andGameVipLevel:ptl->getUserFromList().gameVIPLevel];
        [[[message getUser] getEntryAnimation] setProPertyWithID:ptl->m_User.AnimationID
                                                         andPath:[NSString stringWithUTF8String:ptl->getUserFromList().AnimationPath.c_str()]
                                                      andVersion:[NSString stringWithUTF8String:ptl->getUserFromList().AnimationVer.c_str()]
                                                          isShow:ptl->getUserFromList().isAnimationShow];
        [message addUserIntoList:[message getUser]];
        ptl->PopUserList();
    }
    return message;
}
