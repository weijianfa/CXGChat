//
//  PtlSyncMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlSyncAnchorMsg::PtlSyncAnchorMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 7;
    m_nSubType = 2;
    
    Json::Value::iterator itc = buf.begin();
    m_User.userID = (*itc)["ct"]["bb"].asString();
    m_User.nickName = (*itc)["ct"]["p"].asString();
    m_User.headIcon = (*itc)["ct"]["j"].asString();
    m_User.gameUid = (*itc)["ct"]["a4"].asString();
    
    m_User.userLevel = (*itc)["ct"]["o"].asInt();
    m_User.fansLevel = (*itc)["ct"]["b3"].asInt();
    m_User.richLevel = (*itc)["ct"]["h"].asInt();
    
    m_User.terminal = (*itc)["ct"]["c3"].asInt();
    m_User.roleID = (*itc)["ct"]["y"].asInt();
    m_User.roomRole = (*itc)["ct"]["a1"].asString();
    m_User.userType = (*itc)["ct"]["a8"].asInt();
    m_User.sortNum = (*itc)["ct"]["a2"].asDouble();
    m_User.gameZoneName = (*itc)["ct"]["b1"].asString();
    
    m_User.isAllowPrivateChat = (*itc)["ct"]["x"].asBool();
    m_User.isReconnect = (*itc)["ct"]["m"].asBool();
    m_User.isAnchor = (*itc)["ct"]["l"].asBool();
}

PtlSyncCharmMsg::PtlSyncCharmMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 7;
    m_nSubType = 3;
    
    Json::Value::iterator itc = buf.begin();
    m_User.userID = std::to_string((*itc)["ct"]["bb"].asInt());
    m_User.fansLevel = (*itc)["ct"]["b"].asInt();
    
    m_nExtraProperty = (*itc)["ct"]["a"].asUInt();
}

PtlRankSumMsg::PtlRankSumMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 7;
    m_nSubType = 4;
    
    Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_nExtraProperty = ctobject["a"].asInt();
        }
    }
}
