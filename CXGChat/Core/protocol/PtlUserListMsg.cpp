//
//  PtlUserListMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"


PtlUserListMsg::PtlUserListMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlUserListMsg\n");
    
    this->type = 3;  // msg
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["escape"].asString();
    
    Json::Value::iterator itc2 = (*itc)["ct"].begin();
    
    long count = (*itc2)["e"].asInt();
    
    itc2++;
    
    Json::Value::iterator itc3 = (*itc2)["h"].begin();  // userlist
    
//    while(itc3++) {
//        long headid =(*itc3)["j"].asInt();
//        long userid = (*itc3)["bb"].asInt();
//        
//    }
}
