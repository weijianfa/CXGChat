//
//  PtlOpenChatMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"

// 开启关闭公聊，不解析
PtlCloseChatMsg::PtlCloseChatMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlCloseChatMsg\n");
    
    this->type = 6;  // msg
    this->subType = 1;   //
    
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
            nickName = ctobject["userName"].asString();
            userID = ctobject["userId"].asUInt();
            
            simpleProperty = ctobject["flag"].asInt();  // 1 开启  0 关闭
            
        }
    }
}
