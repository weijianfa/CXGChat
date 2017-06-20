//
//  PtlNotiManagerMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlNotiManagerMsg::PtlNotiManagerMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 6;
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
            m_User.userID = ctobject["b"]["bb"].asString();
            m_User.nickName = ctobject["b"]["p"].asString();
            m_User.gameUid = ctobject["b"]["a4"].asString();
            
            m_User.fansLevel = ctobject["b"]["b3"].asInt();
            m_User.richLevel = ctobject["b"]["h"].asInt();
            m_User.roomRole = ctobject["b"]["a1"].asString();
            
            m_User.terminal = ctobject["b"]["c3"].asInt();
            m_User.roleID = ctobject["b"]["y"].asInt();
            m_User.roomRole = ctobject["b"]["a1"].asString();
            m_User.userType = ctobject["b"]["a8"].asInt();
            m_User.sortNum = ctobject["b"]["a2"].asDouble();
            m_User.gameZoneName = ctobject["b"]["b1"].asString();
            
            m_ReceiveUser.userID = ctobject["f"]["bb"].asString();
            m_ReceiveUser.nickName = ctobject["f"]["p"].asString();
            m_ReceiveUser.gameUid = ctobject["f"]["a4"].asString();
            
            m_ReceiveUser.fansLevel = ctobject["f"]["b3"].asInt();
            m_ReceiveUser.richLevel = ctobject["f"]["h"].asInt();
            m_ReceiveUser.roomRole = ctobject["f"]["a1"].asString();
            
            m_ReceiveUser.terminal = ctobject["f"]["c3"].asInt();
            m_ReceiveUser.roleID = ctobject["f"]["y"].asInt();
            m_ReceiveUser.roomRole = ctobject["f"]["a1"].asString();
            m_ReceiveUser.userType = ctobject["f"]["a8"].asInt();
            m_ReceiveUser.sortNum = ctobject["f"]["a2"].asDouble();
            m_ReceiveUser.gameZoneName = ctobject["f"]["b1"].asString();
            
            m_nExtraProperty = ctobject["h"].asInt();  //1、设置 2、取消
        }
    }
}
