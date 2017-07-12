//
//  PtlGiftMsg.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlGiftMsg::PtlGiftMsg(int ret,Json::Value::iterator itc): PtlBase(ret, itc)
{
    m_nType = 2;
    m_nSubType = 0;
    
    //Json::Value::iterator itc = buf.begin();
    //std::string typeStr = (*itc)["escapeflag"].asString();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_User.nickName = ctobject["b9"].asString();
            m_User.userID = std::to_string(ctobject["bb"].asUInt());
            m_User.equipScore = ctobject["d"].asInt();
            m_User.fansLevel = ctobject["e"].asInt();
            m_User.richLevel = ctobject["b7"].asInt();
            m_User.userLevel = ctobject["a8"].asInt();
            m_User.gameRoleType = ctobject["a3"].asInt();
            m_User.gameVIPLevel = ctobject["b1"].asInt();
            m_User.gameUid = ctobject["c1"].asString();
            m_User.userType = ctobject["c2"].asInt();
            
            m_ReceiveUser.userID = std::to_string(ctobject["b2"].asUInt());
            m_ReceiveUser.nickName = ctobject["b9"].asString();
            m_ReceiveUser.gameZoneName = ctobject["b5"].asString();
            
            m_Gift.isAutoCombo = ctobject["a"].asBool();
            m_Gift.comboGroupNum = ctobject["b"].asInt();
            m_Gift.comboNum = ctobject["c"].asInt();
            m_Gift.isCombo = ctobject["x"].asBool();
            m_Gift.count = ctobject["i"].asInt();
            m_Gift.icon = ctobject["j"].asString();
            m_Gift.giftID = ctobject["n"].asInt();
            m_Gift.name = ctobject["q"].asString();
            m_Gift.type = ctobject["v"].asInt();
            m_Gift.uniqueID = ctobject["w"].asString();
            m_Gift.isFree = ctobject["y"].asInt();
        }
    }
}
