//
//  PtlBase.hpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#ifndef PtlBase_hpp
#define PtlBase_hpp

#include "../Includes/PrecompileConfig.h"

struct USER
{
    std::string userID;
    std::string nickName;
    std::string headIcon;
    std::string gameUid;
    std::string roomRole;
    std::string gameZoneName;
    std::string specialNo;
    
    int terminal;
    int userType;
    int roleID;
    int fansLevel;
    int richLevel;
    int userLevel;
    int equipScore;
    int gameRoleType;
    int gameVIPLevel;
    
    long sortNum;
    
    bool isAnchor;
    bool isReconnect;
    bool isAllowPrivateChat;
    
    int AnimationID;
    std::string AnimationPath;
    std::string AnimationVer;
    bool isAnimationShow;
    
    std::string medal;
    
    USER()
    {
        userID   = "";
        nickName = "";
        headIcon = "";
        gameUid  = "";
        roomRole = "";
        gameZoneName= "";
        specialNo = "";
        
        terminal = 0;
        userType = 0;
        roleID   = 0;
        sortNum  = 0;
        fansLevel = 0;
        richLevel = 0;
        userLevel = 0;
        equipScore= 0;
        gameRoleType = 0;
        gameVIPLevel = 0;
        
        isAnchor = false;
        isReconnect = false;
        isAllowPrivateChat = true;
        
        AnimationID = 0;
        AnimationPath = "";
        AnimationVer = "";
        isAnimationShow = true;
        
        medal = "";
    }
};

struct GIFT
{
    std::string name;
    std::string icon;
    std::string uniqueID;
    
    int giftID;
    int count;
    int type;
    int comboNum;
    int comboGroupNum;
    int version;
    
    bool isAutoCombo;
    bool isCombo;
    bool isFree;
    
    GIFT()
    {
        name = "";
        icon = "";
        uniqueID ="";
        
        giftID = 0;
        count  = 0;
        type = 0;
        comboNum = 0;
        comboGroupNum = 0;
        version = 0;
        
        isAutoCombo = false;
        isCombo = false;
        isFree = true;
    }
};

typedef std::queue<USER> USER_LIST;

std::string unescape(char* str);
std::string translateGUID(std::string guid);
class PtlBase
{
public:
    PtlBase(int ret,Json::Value::iterator buf);
    ~PtlBase();
    
    static PtlBase* getProtocol(int nType, Json::Value::iterator buff);
    
    USER getUserFromList();
    bool PopUserList();
    
private:
    bool PushUserList(USER& user);
    
public:
    
    int m_nType;  // 消息类型 1， 聊天消息（飞屏，广播），2 ，礼物消息 3.系统消息，4.进入聊天室【可能入场特效】
    int m_nSubType; // 小类，（1-0普通聊天消息，1-1飞屏，1-2广播）
    long m_nExtraProperty; // 简单属性
    
    std::string m_strMsg;
    
    USER m_User;
    USER m_ReceiveUser;
    GIFT m_Gift;
    USER_LIST m_UserList;
};


class PtlUserMsg: public PtlBase {
public:
    PtlUserMsg(int ret, Json::Value::iterator buf);
};

class PtlGiftMsg: public PtlBase {
public:
    PtlGiftMsg(int ret,Json::Value::iterator buf);
};

class PtlLoginRet: public PtlBase {
public:
    PtlLoginRet(int ret,Json::Value::iterator buf);
};

class PtlLoginSeccess: public PtlBase {
public:
    PtlLoginSeccess(int ret,Json::Value::iterator buf);
};

class PtLeaveRoom: public PtlBase {
public:
    PtLeaveRoom(int ret,Json::Value::iterator buf);
};

class PtlSysMsg: public PtlBase {
public:
    PtlSysMsg(int ret,Json::Value::iterator buf);
};

class PtlFeiPingMsg: public PtlBase {
public:
    PtlFeiPingMsg(int ret, Json::Value::iterator buf);
};

// 广播
class PtlBroadcastMsg: public PtlBase {
public:
    PtlBroadcastMsg(int ret, Json::Value::iterator buf);
};

// 头条
class PtlHeadTipMsg: public PtlBase {
public:
    PtlHeadTipMsg(int ret, Json::Value::iterator buf);
};

// 同步主播信息
class PtlSyncAnchorMsg: public PtlBase {
public:
    PtlSyncAnchorMsg(int ret, Json::Value::iterator buf);
};

//同步主播魅力等级
class PtlSyncCharmMsg: public PtlBase {
public:
    PtlSyncCharmMsg(int ret, Json::Value::iterator buf);
};

//同步房间用户数量
class PtlSyncUserContMsg: public PtlBase {
public:
    PtlSyncUserContMsg(int ret,Json::Value::iterator buf);
};

// 等级提升
class PtlLevelUpMsg: public PtlBase {
public:
    PtlLevelUpMsg(int ret, Json::Value::iterator buf);
};

// 天龙VIP等级提升
class PtlVipLevelUpMsg: public PtlBase {
public:
    PtlVipLevelUpMsg(int ret, Json::Value::iterator buf);
};

// 7日排行榜总数
class PtlRankSumMsg: public PtlBase {
public:
    PtlRankSumMsg(int ret, Json::Value::iterator buf);
};

// combo消息
class PtlComboMsg: public PtlBase {
public:
    PtlComboMsg(int ret, Json::Value::iterator buf);
    PtlComboMsg();
};

// 提升管理员
class PtlNotiManagerMsg: public PtlBase {
public:
    PtlNotiManagerMsg(int ret, Json::Value::iterator buf);
};

// 踢人消息
class PtlNotiKickMsg: public PtlBase {
public:
    PtlNotiKickMsg(int ret, Json::Value::iterator buf);
};

// 取消禁言
class PtlResumeUserMsg: public PtlBase {
public:
    PtlResumeUserMsg(int ret, Json::Value::iterator buf);
};

// 禁言
class PtlUnResumeUserMsg: public PtlBase {
public:
    PtlUnResumeUserMsg(int ret, Json::Value::iterator buf);
};

// 关闭聊天
class PtlCloseChatMsg: public PtlBase {
public:
    PtlCloseChatMsg(int ret, Json::Value::iterator buf);
};

// 直播结束
class PtlRoomCloseMsg: public PtlBase {
public:
    PtlRoomCloseMsg(int ret, Json::Value::iterator buf);
};

// 直播开始
class PtlRoomOpenMsg: public PtlBase {
public:
    PtlRoomOpenMsg(int ret, Json::Value::iterator buf);
};

// 用户信息
class PtlUserInfoMsg: public PtlBase {
public:
    PtlUserInfoMsg(int ret, Json::Value::iterator buf);
};

// 用户列表
class PtlUserListMsg: public PtlBase {
public:
    PtlUserListMsg(int ret, Json::Value::iterator buf);
};

//设置、取消关注
class PtlSetAttentionMsg: public PtlBase {
public:
    PtlSetAttentionMsg(int ret, Json::Value::iterator buf);
};

#endif /* PtlBase_hpp */
