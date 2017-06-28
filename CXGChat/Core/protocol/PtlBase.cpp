
//
//  PtlBase.cpp
//  Test2
//
//  Created by Lu Jinfei on 2017/3/2.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#include "PtlBase.hpp"
#include "ChatMsgInfo.h"

long hex2dec(char * s)
{
    int L = (int)strlen(s);
    char c;
    long re = 0;
    while ((c = s++[0]))
    {
        if (c >= '0' && c <= '9')
        {
            c -= 48;
        }
        else
        {
            c = c>'Z' ? c - 32 : c;
            c -= 'A' - 10;
        }
        re += c*pow(16.0, --L);
    }
    
    return re;
}

std::string unescape(char* str)
{
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    const int nMultiByte = 2;
#else
    int nByte = 0;
    const int nMultiByte = 3;
#endif
    
    char* re = (char*)calloc(strlen(str) + 1, 1);
    char* _str;
    char* _re = re;
    char code[5] = { 0 };
    wchar_t wc;
    int n;
    
    while (str)
    {
        _str = strchr(str, '%');
        if (!_str)
        {
            break;
        }
        
        if ((n = _str - str))
        {
            memcpy(_re, str, n);
            _re += n;
        }
        
        memset(code, 0, sizeof(code));
        if (_str[1] == 'u')
        {
            memcpy(code, _str + 2, 4);
            str = _str + 6;
            wc = hex2dec(code);
            memset(code, 0, 5);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            WideCharToMultiByte(CP_OEMCP, NULL, &wc, -1, (char*)code, nMultiByte, NULL, FALSE);
            memcpy(_re, code, nMultiByte);
            _re += nMultiByte;
#else
            wcstombs(code, &wc, nMultiByte);
            nByte = (int)strlen(code);
            memcpy(_re, code, nByte);
            _re += nByte;
#endif
        }
        else
        {
            memcpy(code, _str + 1, 2);
            str = _str + 3;
            _re[0] = hex2dec(code);
            _re++;
        }
    }
    
    strcpy(_re, str);
    std::string rt(re);
    free(re);
    re = NULL;
    
    return rt;
}

PtlBase::PtlBase(int ret,Json::Value::iterator itc)
{
    m_nType = 0;
    m_nSubType = 0;
    m_nExtraProperty = 0;
    
    m_strMsg = "";
}

PtlBase::~PtlBase()
{
}

PtlBase* PtlBase::getProtocol(int nType, Json::Value::iterator itc)
{
    switch(nType)
    {
        case USER_MSG:
        case USER_PUB_MSG:
        case USER_PRI_MSG:
            return new PtlUserMsg(nType, itc);
            break;
        case SYST_MSG:
            return new PtlSysMsg(nType, itc);
            break;
        case GIFT_MSG:
            return new PtlGiftMsg(nType, itc);
            break;
        case LOGN_RET:
            return new PtlLoginRet(nType, itc);
            break;
        case LOGIN_SEC_MSG:
            return new PtlLoginSeccess(nType, itc);
            break;
        case CONT_MSG:
            return new PtlSyncUserContMsg(nType, itc);
            break;
        case FEIPING_MSG:
            return new PtlFeiPingMsg(nType, itc);
            break;
        case BROADCT_MSG:
            return new PtlBroadcastMsg(nType, itc);
            break;
        case HEADTIP_MSG:
            return new PtlHeadTipMsg(nType, itc);
            break;
        case SYNC_MSG:
            return new PtlSyncAnchorMsg(nType, itc);
            break;
        case CHARM_MSG:
            return new PtlSyncCharmMsg(nType, itc);
            break;
        case LEVLEUP_MSG:
            return new PtlLevelUpMsg(nType, itc);
            break;
        case VIPUP_MSG:
            return new PtlVipLevelUpMsg(nType, itc);
            break;
        case RANKSUM_MSG:
            return new PtlRankSumMsg(nType, itc);
            break;
        case COMBOIT_MSG:
            return new PtlComboMsg(nType, itc);
            break;
        case NOTIMAN_MSG:
            return new PtlNotiManagerMsg(nType, itc);
            break;
        case KICK_MSG:
            return new PtlNotiKickMsg(nType, itc);
            break;
        case RESUME_MSG:
            return new PtlResumeUserMsg(nType, itc);
            break;
        case URESUME_MSG:
            return new PtlUnResumeUserMsg(nType, itc);
            break;
        case OPENCHAT_MSG:
            return new PtlCloseChatMsg(nType, itc);
            break;
        case CLOSE_MSG:
            return new PtlRoomCloseMsg(nType, itc);
            break;
        case OPENI_MSG:
            return new PtlRoomOpenMsg(nType, itc);
            break;
        case USERINTO_MSG:
            return new PtlUserInfoMsg(nType, itc);
            break;
        case USERLIST_MSG:
            return new PtlUserListMsg(nType, itc);
        default:
            return NULL;
            break;
    }
    
    return NULL;
}

bool PtlBase::PushUserList(USER &user)
{
    if(user.userID.empty())
        return false;
    
    m_UserList.push(user);
    return true;
}

bool PtlBase::PopUserList()
{
    if(!m_UserList.empty())
        m_UserList.pop();
    
    return true;
}

USER PtlBase::getUserFromList()
{
    USER user;
    if(m_UserList.empty())
        return user;
    
    user = m_UserList.front();
    return user;
}
