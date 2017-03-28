//
//  PtlSysMsg.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"


PtlSysMsg::PtlSysMsg(int ret,Json::Value  buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlSysMsg\n");
    this->type = 3;  // msg
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["escape"].asString();
    
    std::string ct = (*itc)["ct"].asString();
    
    userID = "SYS";
    
    if(ct.length() > 0) {
        ct = unescape((char*)ct.c_str());
        
        Json::Reader ctreader;
        Json::Value ctobject;
        std::string strMsg = "";
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            msg = ctobject["mes"].asString();
        }
    }
}
