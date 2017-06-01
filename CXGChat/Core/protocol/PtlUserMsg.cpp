//
//  PtlUserMsg.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//
#include "PtlBase.hpp"

PtlUserMsg::PtlUserMsg(int ret,Json::Value  buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlUserMsg\n");
    this->type = 1;  // msg

    Json::Value::iterator itc = buf.begin();
    
    msg = (*itc)["ct"].asString();
    
    userID = (*itc)["e"]["bb"].asString();
    nickName = (*itc)["e"]["p"].asString();
    user2ID = "";
    nickName2 = "";
    
    fensi = (*itc)["e"]["b3"].asInt();
    caifu = (*itc)["e"]["h"].asInt();
    jueseStr = (*itc)["e"]["a1"].asString();
    gameUid = (*itc)["e"]["a4"].asString();
    
    std::string typeStr = (*itc)["b"].asString();
    int nType = atoi(typeStr.c_str());
    switch (nType)
    {
        case 0:
            this->subType = 0;
            break;
        case 1:
            this->subType = 3;
            break;
        case 2:
            this->subType = 4;
            user2ID = (*itc)["f"]["bb"].asString();
            nickName2 = (*itc)["f"]["p"].asString();
            gameUid2 = (*itc)["f"]["a4"].asString();
            break;
        default:
            break;
    }
}

