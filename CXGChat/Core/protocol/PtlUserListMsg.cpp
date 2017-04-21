//
//  PtlUserListMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"


PtlUserListMsg::PtlUserListMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlUserListMsg\n");
    
    this->type = 7;  // msg
    
    Json::Value::iterator itc = buf.begin();
    std::string typeStr = (*itc)["escape"].asString();
    
    Json::Value::iterator itc2 = (*itc)["ct"].begin();
    
    itc2++;
    //long count = (*itc2)["e"].asInt();
    
    int i = 0;
    
    UserInfo* puser = NULL;
    
    for (Json::ValueIterator itr = (*itc2)["h"].begin(); itr != (*itc2)["h"].end(); itr++)
    {
        Json::Value t=(Json::Value)*itr;
        std::string nickName = t["p"].asString();
        std::string userID = t["bb"].asString();
        std::string head = t["j"].asString();
        
        UserInfo* user= new UserInfo(userID, nickName, head);
        
        if(0 == i) {
            this->user = user;
            puser = user;
        } else {
            puser->nextp = user;
            puser = user;
        }
        
        i++;
    }
}
