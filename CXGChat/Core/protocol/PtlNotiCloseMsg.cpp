//
//  PtlNotiCloseMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlRoomCloseMsg::PtlRoomCloseMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 6;
    m_nSubType = 5;
    
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
            m_nExtraProperty = ctobject["b"].asInt();
        }
    }
}

