//
//  PtlOpenChatMsg.cpp
//  CXGChat
//
//  Created by Lu Jinfei on 2017/4/13.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"

// 开启关闭公聊
PtlCloseChatMsg::PtlCloseChatMsg(int ret, Json::Value buf):PtlBase(ret, buf)
{
    m_nType = 6;
    m_nSubType = 1;
    
    Json::Value::iterator itc = buf.begin();
    std::string ct = (*itc)["ct"].asString();
    if(!ct.empty())
    {
        ct = unescape((char*)ct.c_str());
        Json::Reader ctreader;
        Json::Value ctobject;
        
        if (ctreader.parse(ct.c_str(), ctobject))
        {
            m_User.nickName = ctobject["userName"].asString();
            m_User.userID = ctobject["userId"].asUInt();
            
            m_nExtraProperty = ctobject["flag"].asInt();  // 1 开启  0 关闭
            m_strMsg = std::to_string(ctobject["roomeId"].asDouble());
        }
    }
}
