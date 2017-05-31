//
//  PtlBase.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "json.h"

const int USER_MSG = (0<<16) + 2;
const int USER_PUB_MSG = (1<<16) + 2; //对某人公开说
const int USER_PRI_MSG = (2<<16) + 2; //对某人私聊

const int SYST_MSG = (24<<16) + 1;
const int GIFT_MSG = (3<<16) + 1;
const int CONT_MSG = (84<<16) + 1;  // men count in room
const int LOGN_RET = 0;

const int FEIPING_MSG = (74<<16) + 1;  // 飞屏
const int BROADCT_MSG = (31<<16) + 1;  // 广播
const int HEADTIP_MSG = (12<<16) + 1;  // 头条
const int SYNC_MSG    = (79<<16) + 1;  // 同步魅力等级
const int LEVLEUP_MSG = (20<<16) + 1;  // 等级提升
const int VIPUP_MSG   = (81<<16) + 1;  // 天龙角色VIP提升
const int COMBOIT_MSG = (82<<16) + 1;  // combo消息
const int NOTIMAN_MSG = (13<<16) + 1;  // 提示用户提升管理员
const int KICK_MSG    = (0<<16)  + 4;  // 踢人消息
const int RESUME_MSG  = (2<<16)  + 4;  // 取消警言
const int URESUME_MSG = (1<<16)  + 4;  // 警言
const int OPENCHAT_MSG= (11<<16) + 1;  // 开启公聊
const int CLOSE_MSG   = (18<<16) + 1;  // 关闭直播通知
const int OPENI_MSG   = (15<<16) + 1;  // 开启直播通知
const int USERLIST_MSG= (0<<16)  + 6;  // 用户列表
const int USERINTO_MSG= (4<<16)  + 2;  // 用户信息
const int RANKSUM_MSG    = (93<<16) + 1;  // 7日排行榜总数

UserInfo::UserInfo(std::string userID, std::string nickName, std::string head){
    this->userID = userID;
    this->nickName = nickName;
    this->head = head;
}

int PtlBase::getRetCode() {
    return this->retCode;
}

PtlBase::PtlBase(int ret,Json::Value buf) {
    this->retCode = ret;
}

PtlBase::PtlBase() {
    this->retCode = 0;
}

PtlBase* PtlBase::getProtocol(char* buf) {
    
    Json::Reader reader;
    Json::Value object;
    
    try
    {
        if (!reader.parse(buf, object))
        {
            return NULL;
        }
    }
    catch (std::exception& e)
    {
        return NULL;
    }
    
    std::string retcode = object["retcode"].asString();
    int ncode = atoi(retcode.c_str());
    
    Json::Value msgObj = object["msg"];
    if (msgObj.empty()) {
        return new PtlBase(ncode, 0);
    }
    
    Json::Value::iterator itc = msgObj.begin();
    std::string action = (*itc)["b"].asString();
    std::string msgtype = (*itc)["c"].asString();
    int nMsgType = atoi(msgtype.c_str());
    int nAction = atoi(action.c_str());
    
    printf("receive %d,%d:  %d\n", nAction, nMsgType, ncode);
    
    switch((nAction<<16)+ nMsgType) {
        case USER_MSG:
            return new PtlUserMsg(ncode, object["msg"]);
        case USER_PUB_MSG:
            return new PtlUserMsg(ncode, object["msg"]);//return new PtlUserMsgPub(ncode, object["msg"]);
        case USER_PRI_MSG:
            return new PtlUserMsg(ncode, object["msg"]);//return new PtlUserMsgPri(ncode, object["msg"]);
        case SYST_MSG:
            return new PtlSysMsg(ncode, object["msg"]);
        case GIFT_MSG:
            return new PtlGiftMsg(ncode, object["msg"]);
        case LOGN_RET:
            return new PtlLoginRet(ncode, object["msg"]);
        case CONT_MSG:
            return new PtlContMsg(ncode, object["msg"]);
        case FEIPING_MSG:
            return new PtlFeiPingMsg(ncode, object["msg"]);
        case BROADCT_MSG:
            return new PtlBroadcastMsg(ncode, object["msg"]);
        case HEADTIP_MSG:
            return new PtlHeadTipMsg(ncode, object["msg"]);
        case SYNC_MSG:
            return new PtlSyncMsg(ncode, object["msg"]);
        case LEVLEUP_MSG:
            return new PtlLevelUpMsg(ncode, object["msg"]);
        case VIPUP_MSG:
            return new PtlVipLevelUpMsg(ncode, object["msg"]);
        case RANKSUM_MSG:
            return new PtlRankSumMsg(ncode, object["msg"]);
        case COMBOIT_MSG:
            return new PtlComboMsg(ncode, object["msg"]);
        case NOTIMAN_MSG:
            return new PtlNotiManagerMsg(ncode, object["msg"]);
        case KICK_MSG:
            return new PtlNotiKickMsg(ncode, object["msg"]);
        case RESUME_MSG:
            return new PtlResumeUserMsg(ncode, object["msg"]);
        case URESUME_MSG:
            return new PtlUnResumeUserMsg(ncode, object["msg"]);
        case OPENCHAT_MSG:
            return new PtlCloseChatMsg(ncode, object["msg"]);
        case CLOSE_MSG:
            return new PtlRoomOpenMsg(ncode, object["msg"]);
        case OPENI_MSG:
            return new PtlRoomOpenMsg(ncode, object["msg"]);
        case USERLIST_MSG:
            return new PtlUserListMsg(ncode, object["msg"]);
        case USERINTO_MSG:
            return new PtlUserInfoMsg(ncode, object["msg"]);
        default:
            return new PtlBase(ncode, object["msg"]);
    }
}

std::string PtlBase::getDisplayMsg() {
    return this->nickName + ": " + this->msg;
}
