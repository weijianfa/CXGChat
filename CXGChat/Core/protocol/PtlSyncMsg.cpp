//
//  PtlSyncMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlSyncAnchorMsg::PtlSyncAnchorMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 7;
    m_nSubType = 2;
    
    //Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_User.userID = ctobject["bb"].asString();
            m_User.nickName = ctobject["p"].asString();
            m_User.headIcon = ctobject["j"].asString();
            m_User.gameUid = ctobject["a4"].asString();
            
            m_User.userLevel = ctobject["o"].asInt();
            m_User.fansLevel = ctobject["b3"].asInt();
            m_User.richLevel = ctobject["h"].asInt();
            
            m_User.terminal = ctobject["c3"].asInt();
            m_User.roleID = ctobject["y"].asInt();
            m_User.roomRole = ctobject["a1"].asString();
            m_User.userType = ctobject["a8"].asInt();
            m_User.sortNum = ctobject["a2"].asDouble();
            m_User.gameZoneName = ctobject["b1"].asString();
            
            m_User.isAllowPrivateChat = ctobject["x"].asInt();
            m_User.isReconnect = ctobject["m"].asInt();
            m_User.isAnchor = ctobject["l"].asBool();
        }
    }
}

PtlSyncCharmMsg::PtlSyncCharmMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 7;
    m_nSubType = 3;
    
    //Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    
    ct = unescape((char*)ct.c_str());
    Json::Reader ctreader;
    Json::Value ctobject;
    
    if (ctreader.parse(ct.c_str(), ctobject))
    {
        m_User.userID = std::to_string(ctobject["bb"].asUInt());
        m_User.fansLevel = ctobject["b"].asInt();
        
        m_nExtraProperty = ctobject["a"].asUInt();
    }
}

PtlRankSumMsg::PtlRankSumMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 7;
    m_nSubType = 4;
    
    //Json::Value::iterator itc = buf.begin();
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
