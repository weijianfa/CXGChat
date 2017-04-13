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
}
