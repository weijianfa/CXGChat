//
//  PtlLoginRet.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlLoginRet::PtlLoginRet(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 4;
    m_nSubType = 0;
    
    //Json::Value::iterator itc = buf.begin();
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
    
    std::string g = (*itc)["ct"]["g"].asString();
    if(!g.empty())
    {
        //g = unescape((char*)g.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        if (ctreader.parse(g.c_str(), ctobject))
        {
            m_User.isAnimationShow = ctobject["c2"].asBool();
            m_User.AnimationID = ctobject["c5"].asInt();
            m_User.AnimationPath = ctobject["c6"].asString();
            m_User.AnimationVer = ctobject["c7"].asInt();
        }
    }
}

PtLeaveRoom::PtLeaveRoom(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 4;
    m_nSubType = 1;
    
    //Json::Value::iterator itc = buf.begin();
    m_User.userID = (*itc)["ct"].asString();
}
