//
//  PtlFeiPingMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

// 飞屏
PtlFeiPingMsg::PtlFeiPingMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 1;
    m_nSubType = 3;
    
    //Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_strMsg = ctobject["c"].asString();
            
            m_User.userID = std::to_string(ctobject["bb"].asUInt());
            m_User.richLevel = ctobject["e"].asInt();
            m_User.fansLevel = ctobject["a"].asInt();
            m_User.nickName = ctobject["h"].asString();
            m_User.medal = std::atoi(ctobject["i"].asString().c_str());
            
            m_nExtraProperty = ctobject["f"].asDouble();
            
            m_Gift.giftID = ctobject["b"].asInt();
        }
    }
}
