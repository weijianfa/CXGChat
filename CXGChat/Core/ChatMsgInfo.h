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

#endif
