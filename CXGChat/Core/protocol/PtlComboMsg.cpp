//
//  PtlComboMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"

PtlComboMsg::PtlComboMsg() {
    this->type = 2;  // msg
    this->subType = 2; // 2-2
}

PtlComboMsg::PtlComboMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlComboMsg\n");
    
    this->type = 2;  // msg
    this->subType = 2; // 2-2
    
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
            if(ctobject.empty()) {
                return;
            }
            
            int i = 0;
            
            PtlBase* current = this;
            
            for (Json::ValueIterator itr = ctobject.begin(); itr != ctobject.end(); itr++) {
                Json::Value t=(Json::Value)*itr;
                if(i == 0) {
                    userID = t["bb"].asInt();
                    nickName = t["i"].asString();
                    giftid = t["g"].asInt();
                    giftCount = t["d"].asInt();
                    giftName = "";
                
                    //long autoflag = ctobject["a"].asInt();// auto
                    giftGroupCount = t["b"].asInt();        // group count
                    giftUUID = t["c"].asString();           //
                    giftPrice = t["h"].asInt();             // price
                } else {
                    PtlComboMsg* next = new PtlComboMsg();
                    next->userID = t["bb"].asInt();
                    next->nickName = t["i"].asString();
                    next->giftid = t["g"].asInt();
                    next->giftCount = t["d"].asInt();
                    next->giftName = "";
                    next->giftGroupCount = t["b"].asInt();
                    next->giftUUID = t["c"].asString();
                    next->giftPrice = t["h"].asInt();
                    
                    current->nextp = next;
                    current = current->nextp;
                }
                i++;
            }
        }
    }
}
