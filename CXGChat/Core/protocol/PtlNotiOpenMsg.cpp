//
//  PtlNotiOpenMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"


PtlRoomOpenMsg::PtlRoomOpenMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlRoomOpenMsg\n");
    
    this->type = 6;  // msg
    this->subType = 4;   //
    
//    Json::Value::iterator itc = buf.begin();
//    std::string typeStr = (*itc)["escape"].asString();
//    
//    std::string ct = (*itc)["ct"].asString();
//    
//    
//    if(ct.length() > 0) {
//        ct = unescape((char*)ct.c_str());
//        
//        Json::Reader ctreader;
//        Json::Value ctobject;
//        std::string strMsg = "";
//        if (ctreader.parse(ct.c_str(), ctobject))
//        {
//
//            
//        }
//    }
}
