//
//  PtlBase.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "json.h"

const int USER_MSG = (0<<8) + 2;
const int SYST_MSG = (24<<8) + 1;
const int GIFT_MSG = (3<<8) + 1;
const int LOGN_RET = 0;

int PtlBase::getRetCode() {
    return this->retCode;
}

PtlBase::PtlBase(int ret,Json::Value buf) {
    this->retCode = ret;
}

PtlBase* PtlBase::getProtocol(char* buf) {
    
    Json::Reader reader;
    Json::Value object;
    
    try
    {
        if (!reader.parse(buf, object))
        {
            return NULL;
        }
    }
    catch (std::exception& e)
    {
        return NULL;
    }
    
    std::string retcode = object["retcode"].asString();
    int ncode = atoi(retcode.c_str());
    
    Json::Value msgObj = object["msg"];
    if (msgObj.empty()) {
        return new PtlBase(ncode, 0);
    }
    
    Json::Value::iterator itc = msgObj.begin();
    std::string action = (*itc)["b"].asString();
    std::string msgtype = (*itc)["c"].asString();
    int nMsgType = atoi(msgtype.c_str());
    int nAction = atoi(action.c_str());
    
    printf("receive %d,%d:  %d\n", nAction, nMsgType, ncode);
    
    switch((nAction<<8)+ nMsgType) {
        case USER_MSG:
            return new PtlUserMsg(ncode, object["msg"]);
        case SYST_MSG:
            return new PtlSysMsg(ncode, object["msg"]);
        case GIFT_MSG:
            return new PtlGiftMsg(ncode, object["msg"]);
        case LOGN_RET:
            return new PtlLoginRet(ncode, object["msg"]);
        default:
            return new PtlBase(ncode, object["msg"]);
    }
}

std::string PtlBase::getDisplayMsg() {
    return this->nickName + ": " + this->msg;
}
