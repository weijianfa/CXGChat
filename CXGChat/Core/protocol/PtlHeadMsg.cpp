//
//  PtlHeadMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"

PtlHeadTipMsg::PtlHeadTipMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlHeadTipMsg\n");
    
    this->type = 2;  // msg
    this->subType = 3; // toutiaoxiaoxi
    
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["escape"].asString();
    
    std::string ct = (*itc)["ct"].asString();
    
    
    if(ct.length() > 0) {
        ct = unescape((char*)ct.c_str());
        
        Json::Reader ctreader;
        Json::Value ctobject;
        std::string strMsg = "";
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            nickName = ctobject["t"].asString();
            // userID = ctobject["b2"].asInt();
            
            
            juese = 0;
            fensi = ctobject["d"].asInt();
            caifu = ctobject["s"].asInt();
            
            giftName = ctobject["i"].asString();
            giftCount = ctobject["f"].asUInt();
            giftid = ctobject["h"].asUInt();
            simpleProperty = ctobject["j"].asUInt();
            
            
            msg = "我送了" + giftName;
        }
    }
}
