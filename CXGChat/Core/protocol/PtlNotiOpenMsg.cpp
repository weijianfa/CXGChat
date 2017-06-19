//
//  PtlNotiOpenMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlRoomOpenMsg::PtlRoomOpenMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 6;
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
            m_strMsg = ctobject["s"].asString();
        }
    }
}
