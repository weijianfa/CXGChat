//
//  PtlFeiPingMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"

// 飞屏
PtlFeiPingMsg::PtlFeiPingMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlFeiPingMsg\n");
    
    this->type = 3;  // msg
    
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
            msg = ctobject["c"].asString();
            nickName = ctobject["h"].asString();
            userID = ctobject["bb"].asInt();
            int type = ctobject["b"].asInt(); // 飞屏类型
        }
    }

}
