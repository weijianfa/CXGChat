//
//  PtlContMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/3/27.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"


PtlContMsg::PtlContMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlContMsg\n");
    this->type = 11;  // msg
    
    Json::Value::iterator itc = buf.begin();
    //std::string typeStr = (*itc)["escape"].asString();
    
    std::string ct = (*itc)["ct"].asString();
    
    if(ct.length() > 0) {
        Json::Reader ctreader;
        Json::Value ctobject;
        std::string strMsg = "";
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            int commoncount = ctobject["b"].asInt();
            int furturncount = ctobject["c"].asInt();
            printf("chatroom: count, %d,%d", commoncount, furturncount);
            
            
        }
    }

}
