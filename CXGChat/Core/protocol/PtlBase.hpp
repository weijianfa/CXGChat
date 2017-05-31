//
//  PtlBase.hpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#ifndef PtlBase_hpp
#define PtlBase_hpp

#include "json.h"

class UserInfo {
public:
    std::string userID;
    std::string nickName;
    std::string head;
    
    UserInfo *nextp = NULL;
    
    UserInfo(std::string userID, std::string nickName, std::string head);
};

class PtlBase {
    
public:
    int type = 0;  // 消息类型 1， 聊天消息（飞屏，广播），2 ，礼物消息 3.系统消息，4.进入聊天室【可能入场特效】
    int subType = 0; // 小类，（1-0普通聊天消息，1-1飞屏，1-2广播）
    
    long simpleProperty = 0; // 简单属性
    
    long fensi = 0;
    long caifu = 0;
    long juese = 0;
    std::string jueseStr = "";
    long giftCount = 0;
    std::string giftName = "";
    std::string giftUUID = "";
    long giftGroupCount = 1;
    long giftPrice = 0;
    long giftid = 0;
    long giftVersion = 0;
    std::string zipPath = "";
    bool isShowGift = true;
    PtlBase* nextp = NULL;
    UserInfo* user = NULL;
    
protected:
    std::string userID;
    std::string nickName;
    std::string msg;
    
    std::string user2ID;
    std::string nickName2;
    
    int retCode;
    
public:
    PtlBase(int ret,Json::Value  buf);
    PtlBase();
    
    int getRetCode();
    bool isMsg(){return ((type < 10) && (type > 0));};
    std::string getDisplayMsg();
    
    std::string getUserID(){
        return userID;
    }
    
    std::string getNickName()  {
        return nickName;
    }
    
    std::string getMsg() {
        return msg;
    }
    
    static PtlBase* getProtocol(char* buf);
};


class PtlUserMsg: public PtlBase {
public:
    PtlUserMsg(int ret, Json::Value  buf);
};

/*
class PtlUserMsgPub: public PtlBase {
public:
    PtlUserMsgPub(int ret, Json::Value  buf);
};

class PtlUserMsgPri: public PtlBase {
public:
    PtlUserMsgPri(int ret, Json::Value  buf);
};
 */

class PtlGiftMsg: public PtlBase {
public:
    PtlGiftMsg(int ret,Json::Value  buf);
};

class PtlLoginRet: public PtlBase {
public:
    PtlLoginRet(int ret,Json::Value  buf);
};

class PtlSysMsg: public PtlBase {
public:
    PtlSysMsg(int ret,Json::Value  buf);
};

class PtlContMsg: public PtlBase {
public:
    PtlContMsg(int ret,Json::Value buf);
};


// 飞屏
class PtlFeiPingMsg: public PtlBase {
public:
    PtlFeiPingMsg(int ret, Json::Value buf);
};

// 广播
class PtlBroadcastMsg: public PtlBase {
public:
    PtlBroadcastMsg(int ret, Json::Value buf);
};

// 头条
class PtlHeadTipMsg: public PtlBase {
public:
    PtlHeadTipMsg(int ret, Json::Value buf);
};

// 同步主播魅力等级
class PtlSyncMsg: public PtlBase {
public:
    PtlSyncMsg(int ret, Json::Value buf);
};

// 等级提升
class PtlLevelUpMsg: public PtlBase {
public:
    PtlLevelUpMsg(int ret, Json::Value buf);
};

// 天龙VIP等级提升
class PtlVipLevelUpMsg: public PtlBase {
public:
    PtlVipLevelUpMsg(int ret, Json::Value buf);
};

// 7日排行榜总数
class PtlRankSumMsg: public PtlBase {
public:
    PtlRankSumMsg(int ret, Json::Value buf);
};

// combo消息
class PtlComboMsg: public PtlBase {
public:
    PtlComboMsg(int ret, Json::Value buf);
    PtlComboMsg();
};

// 提升管理员
class PtlNotiManagerMsg: public PtlBase {
public:
    PtlNotiManagerMsg(int ret, Json::Value buf);
};

// 踢人消息
class PtlNotiKickMsg: public PtlBase {
public:
    PtlNotiKickMsg(int ret, Json::Value buf);
};

// 取消禁言
class PtlResumeUserMsg: public PtlBase {
public:
    PtlResumeUserMsg(int ret, Json::Value buf);
};

// 禁言
class PtlUnResumeUserMsg: public PtlBase {
public:
    PtlUnResumeUserMsg(int ret, Json::Value buf);
};

// 关闭聊天
class PtlCloseChatMsg: public PtlBase {
public:
    PtlCloseChatMsg(int ret, Json::Value buf);
};

// 直播结束
class PtlRoomCloseMsg: public PtlBase {
public:
    PtlRoomCloseMsg(int ret, Json::Value buf);
};

// 直播开始
class PtlRoomOpenMsg: public PtlBase {
public:
    PtlRoomOpenMsg(int ret, Json::Value buf);
};

// 用户列表
class PtlUserListMsg: public PtlBase {
public:
    PtlUserListMsg(int ret, Json::Value buf);
};

// 用户信息
class PtlUserInfoMsg: public PtlBase {
public:
    PtlUserInfoMsg(int ret, Json::Value buf);
};



#endif /* PtlBase_hpp */
