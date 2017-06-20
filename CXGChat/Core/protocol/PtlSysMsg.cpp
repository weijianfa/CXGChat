//
//  PtlSysMsg.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatRoom.h"


PtlSysMsg::PtlSysMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 3;
    m_nSubType = 0;
    
    //Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
            m_strMsg = ctobject["ct"].asString();
    }
}
