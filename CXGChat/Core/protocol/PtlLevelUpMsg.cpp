//
//  PtlLevelUpMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"

PtlLevelUpMsg::PtlLevelUpMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlLevelUpMsg\n");
    
    this->type = 5;  // msg
    
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
            long userid = ctobject["bb"].asInt();
            long level = 0;                    //ctobject["b"].asInt();
            long type = ctobject["l"].asInt(); // 3 caifu , 2 zubodengji 5 fensi  6 vip 7 ranksum
            switch(type) {
                case 3:
                    this->subType = 3;
                    level = ctobject["a"].asInt();
                    break;
                case 2:
                    this->subType = 2;
                    level = ctobject["c"].asInt();
                    break;
                case 5:
                    this->subType = 5;
                    level = ctobject["c"].asInt();
                    break;
                default:
                    break;
            }
            simpleProperty = level;
            nickName = ctobject["o"].asString();
        }
    }
}


PtlVipLevelUpMsg::PtlVipLevelUpMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlvipLevelUpMsg\n");
    
    this->type = 5;  // msg
    this->subType = 6;
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["escape"].asString();  //or escapeflag
    
    std::string ct = (*itc)["ct"].asString();
    
    if(ct.length() > 0) {
        ct = unescape((char*)ct.c_str());
        
        Json::Reader ctreader;
        Json::Value ctobject;
        std::string strMsg = "";
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            long uid = ctobject["bb"].asInt();
            long level = ctobject["c"].asInt();

            simpleProperty = level;
            userID = uid;
        }
    }
}

PtlRankSumMsg::PtlRankSumMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlRankSumMsg\n");
    
    this->type = 5;  // msg
    this->subType = 7;
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["escape"].asString();  //or escapeflag
    
    std::string ct = (*itc)["ct"].asString();
    
    if(ct.length() > 0) {
        ct = unescape((char*)ct.c_str());
        
        Json::Reader ctreader;
        Json::Value ctobject;
        std::string strMsg = "";
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            long sum = ctobject["c"].asInt();
            simpleProperty = sum;
        }
    }
}
