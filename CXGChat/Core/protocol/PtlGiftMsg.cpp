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
    printf( "chatroom: PtlGiftMsg\n");
    
    this->type = 2;  // msg
    
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
            userID = ctobject["b2"].asInt();
            
            juese = ctobject["c2"].asInt();
            fensi = ctobject["e"].asInt();
            caifu = ctobject["b7"].asInt();
            
            giftName = ctobject["q"].asString();
            giftCount = ctobject["i"].asInt();
            
            msg = "我送了" + giftName;
            
        }
    }
}
