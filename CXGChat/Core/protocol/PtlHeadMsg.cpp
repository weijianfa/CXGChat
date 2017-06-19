//
//  PtlHeadMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlHeadTipMsg::PtlHeadTipMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 2;
    m_nSubType = 3;
    
    Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_ReceiveUser.fansLevel = ctobject["d"].asInt();
            m_ReceiveUser.richLevel = ctobject["a"].asInt();
            m_ReceiveUser.userLevel = ctobject["n"].asInt();
            m_ReceiveUser.nickName = ctobject["o"].asString();
            m_ReceiveUser.userID = ctobject["p"].asInt();
            m_ReceiveUser.gameVIPLevel = ctobject["m"].asInt();
            
            m_User.richLevel = ctobject["s"].asInt();
            m_User.gameUid = ctobject["u"].asString();
            m_User.nickName = ctobject["t"].asString();
            
            m_Gift.giftID = ctobject["h"].asInt();
            m_Gift.name = ctobject["i"].asString();
            m_Gift.count = ctobject["f"].asInt();
            m_Gift.icon = ctobject["g"].asString();
            m_Gift.isAutoCombo = ctobject["b"].asBool();
            m_Gift.comboGroupNum = ctobject["c"].asInt();
            m_Gift.type = ctobject["q"].asInt();
            
            m_nExtraProperty = ctobject["j"].asDouble();
        }
    }
}
