//
//  PtlSetAttentionMsg.cpp
//  CXGChat
//
//  Created by abc on 2017/7/3.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlSetAttentionMsg::PtlSetAttentionMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 6;
    m_nSubType = 8;
    
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_User.userID = std::to_string(ctobject["masterId"].asUInt());
            m_nExtraProperty = ctobject["count"].asUInt();
        }
    }
}
