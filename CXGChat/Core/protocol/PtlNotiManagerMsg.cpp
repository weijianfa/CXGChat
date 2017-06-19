//
//  PtlNotiManagerMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlNotiManagerMsg::PtlNotiManagerMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 6;
    m_nSubType = 3; 
    
    Json::Value::iterator itc = buf.begin();
    m_strMsg = (*itc)["ct"].asString();
    
    m_User.userID = (*itc)["e"]["bb"].asString();
    m_User.nickName = (*itc)["e"]["p"].asString();
    m_User.gameUid = (*itc)["e"]["a4"].asString();
    
    m_User.fansLevel = (*itc)["e"]["b3"].asInt();
    m_User.richLevel = (*itc)["e"]["h"].asInt();
    m_User.roomRole = (*itc)["e"]["a1"].asString();
    
    m_User.terminal = (*itc)["e"]["c3"].asInt();
    m_User.roleID = (*itc)["e"]["y"].asInt();
    m_User.roomRole = (*itc)["e"]["a1"].asString();
    m_User.userType = (*itc)["e"]["a8"].asInt();
    m_User.sortNum = (*itc)["e"]["a2"].asDouble();
    m_User.gameZoneName = (*itc)["e"]["b1"].asString();
    
    m_ReceiveUser.userID = (*itc)["f"]["bb"].asString();
    m_ReceiveUser.nickName = (*itc)["f"]["p"].asString();
    m_ReceiveUser.gameUid = (*itc)["f"]["a4"].asString();
    
    m_ReceiveUser.fansLevel = (*itc)["f"]["b3"].asInt();
    m_ReceiveUser.richLevel = (*itc)["f"]["h"].asInt();
    m_ReceiveUser.roomRole = (*itc)["f"]["a1"].asString();
    
    m_ReceiveUser.terminal = (*itc)["f"]["c3"].asInt();
    m_ReceiveUser.roleID = (*itc)["f"]["y"].asInt();
    m_ReceiveUser.roomRole = (*itc)["f"]["a1"].asString();
    m_ReceiveUser.userType = (*itc)["f"]["a8"].asInt();
    m_ReceiveUser.sortNum = (*itc)["f"]["a2"].asDouble();
    m_ReceiveUser.gameZoneName = (*itc)["f"]["b1"].asString();
            
    m_nExtraProperty = (*itc)["h"].asInt();  //1、设置 2、取消
}
