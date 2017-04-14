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


class PtlBase {
    
public:
    int type = 0;  // 消息类型 1， 聊天消息，2 ，礼物消息 3.系统消息，
    
    long fensi = 0;
    long caifu = 0;
    long juese = 0;
    long giftCount = 0;
    std::string giftName;
    int giftid = 0;
    std::string giftVersion;
    std::string zipPath;
    bool isShowGift = true;
    
protected:
    std::string userID;
    std::string nickName;
    std::string msg;
    
    
    
    int retCode;
    
public:
    PtlBase(int ret,Json::Value  buf);
    
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

// combo消息
class PtlComboMsg: public PtlBase {
public:
    PtlComboMsg(int ret, Json::Value buf);
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
