//
//  PtlLevelUpMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlLevelUpMsg::PtlLevelUpMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 5;
    
    //Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            switch(ctobject["l"].asInt())
            {
                case 3:
                {
                    m_nSubType = 1;
                    m_User.richLevel = ctobject["a"].asInt();
                    m_nExtraProperty = ctobject["b"].asInt();
                }
                    break;
                case 2:
                {
                    m_nSubType = 2;
                    m_User.userLevel = ctobject["c"].asInt();
                    m_nExtraProperty = ctobject["e"].asInt();
                }
                    break;
                case 5:
                {
                    m_nSubType = 3;
                    m_User.fansLevel = ctobject["c"].asInt();
                    m_nExtraProperty = ctobject["q"].asInt();
                }
                    break;
                default:
                    break;
            }
            
            m_User.userID = ctobject["n"]["bb"].asString();
            m_User.nickName = ctobject["n"]["p"].asString();
            m_User.gameUid = ctobject["n"]["a4"].asString();
            
            m_User.fansLevel = ctobject["n"]["b3"].asInt();
            m_User.richLevel = ctobject["n"]["h"].asInt();
            m_User.roomRole = ctobject["n"]["a1"].asString();
            
            m_User.terminal = ctobject["n"]["c3"].asInt();
            m_User.roleID = ctobject["n"]["y"].asInt();
            m_User.roomRole = ctobject["n"]["a1"].asString();
            m_User.userType = ctobject["n"]["a8"].asInt();
            m_User.sortNum = ctobject["n"]["a2"].asDouble();
            m_User.gameZoneName = ctobject["n"]["b1"].asString();
        }
    }
}

PtlVipLevelUpMsg::PtlVipLevelUpMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 5;
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
            m_User.userID = ctobject["bb"].asInt();
            m_nExtraProperty = ctobject["c"].asInt();
        }
    }
}

