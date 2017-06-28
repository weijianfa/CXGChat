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
#define ERR_CONNECT_FAILD	"连接失败"
#define ERR_ENTER_FAILD		"进入失败"
#define ERR_REENTRY_FAILD	"重试失败"
#define ERR_UPLOAD_FAILD	"直播视频数据上传失败，请尝试重新开播"


#define ERR_INVALID_RARAM       "无效参数"
#define ERR_COOKIE_INVALID      "未登录或登录无效"
#define ERR_ROOMID_INVALID      "直播间不存在"
#define ERR_UNPERMISSION        "您被移除直播间 1 小时"
#define ERR_ROOMFULL            "直播间人数已达上限"
#define ERR_UNKNOW_CHATROOM     "系统异常"  //"聊天服务器未找到对应的房间"
#define ERR_ENTER_KICKOUT       "账号已登录其他直播间"
#define ERR_KICKOUT             "系统异常"//"被踢出房间"
#define ERR_STOP_KICKOUT        "系统异常"//"阻止踢人"

#define ERR_USER_UNSPEAK        "您被禁言 30 分钟"
#define ERR_SPEAK_1             "发言间隔不足 2 秒"
#define ERR_SPEAk_2             "发言间隔不足 3 秒"
#define ERR_SPEAK_3             "系统异常"//"聊天内容过长"
#define ERR_SPEAK_NULL          "请输入内容"
#define ERR_FORBID_SPEAK        "系统异常"//"不允许发言"
#define ERR_CHATUSER_NULL       "没有选中聊天对象"
#define ERR_CHATUSER_LEAVE      "聊天对象已离开直播间"

#define ERR_SPEAK_4             "财富等级不足"
#define ERR_ROOM_FORBIDCHAT     "直播间公聊已关闭"
#define ERR_USER_FORBIDSPEAK    "对方已设置拒绝私聊"
#define ERR_PUBSPEAK            "系统异常"//"公聊过滤"
#define ERR_SPEAK_5             "财富等级不足"
#define ERR_GAME_FORBIDSPEAK    "系统异常"//"游戏禁言"


#define ERR_REPETITION_LOGIN	"电脑端已登录，您已被移出直播间"
#define ERR_TERMINAl_MUTEX      "电脑端已登录，您已被移出直播间"

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
    SYNC_MSG    = (86<<16) + 1,  // 同步主播信息
    CHARM_MSG   = (79<<16) + 1,  // 同步主播魅力等级
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
    
    LOGIN_SEC_MSG = (99 << 16) + 99, //登录成功消息
};

#endif
