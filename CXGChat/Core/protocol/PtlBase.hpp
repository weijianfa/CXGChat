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

#endif /* PtlBase_hpp */
