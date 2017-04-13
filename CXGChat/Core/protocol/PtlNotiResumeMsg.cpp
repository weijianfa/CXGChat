//
//  PtlNotiResumeMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"

PtlResumeUserMsg::PtlResumeUserMsg(int ret, Json::Value buf):PtlBase(ret, buf) {
    printf( "chatroom: PtlResumeUserMsg\n");
}
