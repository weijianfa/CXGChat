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
    int type = 0;
    
protected:
    std::string userID;
    std::string nickName;
    std::string msg;
    
    
    
    int retCode;
    
public:
    PtlBase(int ret,Json::Value  buf);
    
    int getRetCode();
    bool isMsg(){return (type == 1);};
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

#endif /* PtlBase_hpp */
