#ifndef __CHATMSG_INFO_H_
#define __CHATMSG_INFO_H_


#define MAX_CHAT_NODE		3
#define KEEPLIVE_INTERVAL   30
#define MAX_WAIT_TIME		20
#define TICKER_TIME         1

#define ENTER               0
#define KEEPLIVE            3
#define SENDMSG				0
#define SENDMSG_PUB         1
#define SENDMSG_PRI         2

#define MSG_TCP_TIMEOUT		"连接超时"
#define MSG_RECONNECT_CHAT	"重新连接"
#define MSG_USER_ENTER		"用户进入"
#define MSG_USER_EXIT		"用户退出"
#define MSG_LIVE_STOP		"直播结束"
#define MSG_LIVE_OK			"直播进行中"
#define MSG_LIVE_FAILD		"直播失败"
#define MSG_LIVE_INTERRUPT	"直播中断"


#define ERR_UNKNOW_ERROR	"未知错误"
#define ERR_COOKIE_INVALID	"登录超时，请重新登录后再次进入畅秀阁。"
#define ERR_CONNECT_FAILD	"连接失败"
#define ERR_ENTER_FAILD		"进入失败"
#define ERR_REENTRY_FAILD	"重试失败"
#define ERR_UPLOAD_FAILD	"直播视频数据上传失败，请尝试重新开播"

#define ERR_ROOMID_INVALID      "无效的房间"
#define ERR_REPETITION_LOGIN	"重复进入房间"
#define ERR_TERMINAl_MUTEX      "PC端角色进入直播间"

enum COMMUNICATION_PROTOCOL
{
    USER_MSG = (0<<16) + 2,
    USER_PUB_MSG = (1<<16) + 2, //对某人公开说
    USER_PRI_MSG = (2<<16) + 2, //对某人私聊
    
    SYST_MSG = (24<<16) + 1,
    GIFT_MSG = (3<<16) + 1,
    CONT_MSG = (84<<16) + 1,
    LOGN_RET = 0,
    
    FEIPING_MSG = (74<<16) + 1,  // 飞屏
    BROADCT_MSG = (31<<16) + 1,  // 广播
    HEADTIP_MSG = (12<<16) + 1,  // 头条
    SYNC_MSG    = (79<<16) + 1,  // 同步魅力等级
    LEVLEUP_MSG = (20<<16) + 1,  // 等级提升
    VIPUP_MSG   = (81<<16) + 1,  // 天龙角色VIP提升
    COMBOIT_MSG = (82<<16) + 1,  // combo消息
    NOTIMAN_MSG = (13<<16) + 1,  // 提示用户提升管理员
    KICK_MSG    = (0<<16)  + 4,  // 踢人消息
    RESUME_MSG  = (2<<16)  + 4,  // 取消警言
    URESUME_MSG = (1<<16)  + 4,  // 禁言
    OPENCHAT_MSG= (11<<16) + 1,  // 开启公聊
    CLOSE_MSG   = (18<<16) + 1,  // 关闭直播通知
    OPENI_MSG   = (15<<16) + 1,  // 开启直播通知
    USERLIST_MSG= (0<<16)  + 6,  // 用户列表
    USERINTO_MSG= (4<<16)  + 2,  // 用户信息
    RANKSUM_MSG = (93<<16) + 1,  // 7日排行榜总数
};

#endif
