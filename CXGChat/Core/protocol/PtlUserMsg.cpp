//
//  PtlUserMsg.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//
#include "PtlBase.hpp"

PtlUserMsg::PtlUserMsg(int ret,Json::Value  buf):PtlBase(ret, buf) {
    printf( "PtlUserMsg\n");
    this->type = 1;  // msg
    
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["b"].asString();
    
    msg = (*itc)["ct"].asString();
    
    userID = (*itc)["e"]["bb"].asString();
    nickName = (*itc)["e"]["p"].asString();
    
    int fensi = (*itc)["e"]["b3"].asInt();
//    int caifu = (*itc)["e"]["bb"].asInt();
    
}

