//
//  PtlUserListMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlUserListMsg::PtlUserListMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 8;
    m_nSubType = 0;
    
    Json::Value::iterator ctitc = (*itc)["ct"].begin();
    m_nExtraProperty = (*ctitc)["c"].asInt();
    
    ctitc++;
    Json::Value::iterator user = (*ctitc)["h"].begin();
    while(user != (*ctitc)["h"].end())
    {
        m_User.userID = (*user)["bb"].asString();
        m_User.nickName = (*user)["p"].asString();
        m_User.gameUid = (*user)["a4"].asString();
        
        m_User.fansLevel = (*user)["b3"].asInt();
        m_User.richLevel = (*user)["h"].asInt();
        m_User.roomRole = (*user)["a1"].asString();
        
        m_User.terminal = (*user)["c3"].asInt();
        m_User.roleID = (*user)["y"].asInt();
        m_User.roomRole = (*user)["a1"].asString();
        m_User.userType = (*user)["a8"].asInt();
        m_User.sortNum = (*user)["a2"].asDouble();
        m_User.gameZoneName = (*user)["b1"].asString();
        user++;
        
        m_UserList.push(m_User);
    }

}
