//
//  PtlUserListMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlUserListMsg::PtlUserListMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 7;
    m_nSubType = 0;
    
}
