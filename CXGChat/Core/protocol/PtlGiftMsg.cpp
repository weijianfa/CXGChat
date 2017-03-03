//
//  PtlGiftMsg.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "zlib.h"
#include "zconf.h"
#include "ChatRoom.h"

PtlGiftMsg::PtlGiftMsg(int ret,Json::Value  buf):PtlBase(ret, buf) {
    printf( "PtlGiftMsg\n");
    
    this->type = 1;  // msg
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["escape"].asString();
    
    std::string ct = (*itc)["ct"].asString();

    if(ct.length() > 0) {
        ct = unescape((char*)ct.c_str());
        
        Json::Reader ctreader;
        Json::Value ctobject;
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            nickName = ctobject["b9"].asString();
            userID = ctobject["b2"].asString();
            
            int fensi = ctobject["e"].asInt();
            int caifu = ctobject["b7"].asInt();
            
            msg = "我送了" + ctobject["q"].asString();
        }
    }
}
