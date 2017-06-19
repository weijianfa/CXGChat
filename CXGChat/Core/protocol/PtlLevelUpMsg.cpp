//
//  PtlLevelUpMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlLevelUpMsg::PtlLevelUpMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 5;
    
    Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_User.userID = ctobject["bb"].asInt();
            m_User.sortNum = ctobject["k"].asDouble();
            
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
                    
                    //这里可能需要一个用户的全量信息
                }
                    break;
                default:
                    break;
            }
        }
    }
}

PtlVipLevelUpMsg::PtlVipLevelUpMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 5;
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
            m_User.userID = ctobject["bb"].asInt();
            m_nExtraProperty = ctobject["c"].asInt();
        }
    }
}

