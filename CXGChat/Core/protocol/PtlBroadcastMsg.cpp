//
//  PtlBroadcastMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlBroadcastMsg::PtlBroadcastMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 1;
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
            m_User.userID = std::to_string(ctobject["bb"].asUInt());
            m_User.nickName = ctobject["f"].asString();
            
            m_ReceiveUser.nickName = std::to_string(ctobject["h"].asUInt());
            
            m_strMsg = ctobject["b"].asString();
            m_nExtraProperty = ctobject["c"].asDouble();s
        }
    }
}
