//
//  PtlComboMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

PtlComboMsg::PtlComboMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 2;
    m_nSubType = 2;
    
    Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            Json::ValueIterator combo = ctobject.begin();
            m_Gift.isAutoCombo = (*combo)["a"].asBool();
            m_Gift.comboGroupNum = (*combo)["b"].asInt();
            m_Gift.count = (*combo)["d"].asInt();
            m_Gift.icon = (*combo)["f"].asString();
            m_Gift.giftID = (*combo)["g"].asInt();
            m_Gift.uniqueID = (*combo)["c"].asString();
            
            m_User.userID = std::to_string((*combo)["bb"].asUInt());
            m_User.nickName = (*combo)["i"].asString();
            m_User.roleID = (*combo)["e"].asInt();
            
            m_nExtraProperty = (*combo)["h"].asInt();
        }
    }
    
 }
