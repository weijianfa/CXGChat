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
            // texiao
            std::string bb = (*itc)["ct"]["g"].asString();
            if(bb == "") {
                return;
            }
            
            std::string ct = (*itc)["ct"]["g"].asString();
            if(ct.length() > 0) {
                ct = unescape((char*)ct.c_str());
                Json::Reader ctreader;
                Json::Value ctobject;
                if (ctreader.parse(ct.c_str(), ctobject))
                {
                    isShowGift = ctobject["c2"].asBool();
                    if(isShowGift) {
                        std::string tempid = ctobject["c5"].asString();
                        giftid = atoi(tempid.c_str());
                        zipPath = ctobject["c6"].asString();
                        giftVersion = ctobject["c7"].asString();
                        giftCount = 1;
                        giftName = "";
                    }
                    
                }
            }
        }
}
