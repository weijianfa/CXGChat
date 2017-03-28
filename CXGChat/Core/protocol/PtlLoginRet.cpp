//
//  PtlLoginRet.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "zlib.h"
#include "zconf.h"
#include "ChatRoom.h"

PtlLoginRet::PtlLoginRet(int ret,Json::Value  buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlLoginRet\n");
    
    this->type = 4;  // msg
    
    Json::Value::iterator itc = buf.begin();
    

        //if (ctreader.parse(ct.c_str(), ctobject))
        {
            nickName = (*itc)["ct"]["p"].asString();
            userID = (*itc)["ct"]["bb"].asString();
            
            juese = (*itc)["ct"]["a8"].asInt();
            fensi = (*itc)["ct"]["b3"].asInt();
            caifu = (*itc)["ct"]["h"].asInt();
            
            msg = "我进来了";
            
        }
    

}
