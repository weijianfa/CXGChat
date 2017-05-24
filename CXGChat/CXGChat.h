//
//  CXGChat.h
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/17.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for CXGChat.
FOUNDATION_EXPORT double CXGChatVersionNumber;

//! Project version string for CXGChat.
FOUNDATION_EXPORT const unsigned char CXGChatVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <CXGChat/PublicHeader.h>

@interface User : NSObject {
    NSInteger fensi;
    NSInteger caifu;
    NSInteger juese;
    
    NSString* userID;
    NSString* nickName;  // nickname
    NSString* head;      // userhead id
    NSString* jueseStr;
}

- (NSInteger) getFensi;
- (NSInteger) getCaifu;
- (NSInteger) getJuese;
- (NSString*) getUserID;
- (NSString*) getNickName;
- (NSString*) getHead;
- (NSString*) getJueseStr;

- (void) setFensi:(NSInteger) fensi;
- (void) setCaifu:(NSInteger) caifu;
- (void) setJuese:(NSInteger) juese;
- (void) setJueseStr:(NSString*) juesestr;

- (void) setUserID:(NSString*) uid;
- (void) setNickName:(NSString*) nick;
- (void) setHead:(NSString*) headimg;

@end

@interface Gift : NSObject {
    NSString* name;
    NSInteger count;
    NSString* zipPath;  // zip path
    NSInteger giftId;   // texiaoid
    NSInteger version;  // texiao version
    NSInteger groupCount; // groupcount
    NSInteger price;
    NSString* uuid;     // combo uuid
    bool isShow; // if show the texiao
}

- (NSString*) getName;
- (NSInteger) getCount;
- (void) setName:(NSString*) name;
- (void) setCount:(NSInteger) count;
- (NSString*) getZipPath;
- (NSInteger) getGiftId;
- (NSInteger) getVersion;
- (bool) getIsShow;
- (NSInteger) getGroupCount;
- (NSInteger) getPrice;
- (NSString*) getUUID;

- (void) setZipPath:(NSString*) path;
- (void) setGiftId:(NSInteger) giftid;
- (void) setVersion:(NSInteger) version;
- (void) setIsShow:(bool) isshow;
- (void) setGroupCount:(NSInteger) count;
- (void) setPrice:(NSInteger) count;
- (void) setUUID:(NSString*) uud;
@end

@interface Message : NSObject {
    NSString* mUid;
    NSString* mNickName;
    NSString* mMsg;
    NSInteger mType;
    NSInteger mSubType;
    NSInteger mSimpleProperty;
    
    Gift* mGift;
    User* mUser;
    
    NSMutableArray* mUserList;
}

- (id) init;

- (void) setUid:(NSString*) uid;
- (void) setNickName:(NSString*) name;
- (void) setMsg:(NSString*) msg;
- (void) setType:(NSInteger) type;
- (void) setSubType:(NSInteger) stype;
- (void) setSimpleProperty:(NSInteger) property;
- (void) addUserList:(User*) user;

- (NSString*) getUid;
- (NSString*) getNickName;
- (NSString*) getMsg;
- (NSInteger) getType;
- (NSInteger) getSubType;
- (NSInteger) getSimpleProperty;
- (Gift*) getGift;
- (User*) getUser;
- (NSMutableArray*) getUserList;
@end



@protocol OnChatDelegate <NSObject>
- (void)onMessage:(Message*) pkg;
- (void)onError:(long) errorCode Msg:(NSString*) msg;
@end



@interface ChatInterface : NSObject

//配置chat服务器地址
- (void)configureRoomHost:(NSString*)host Port:(long)port UID:(NSString*)uid Token:(NSString*)t Rid:(NSString*)rid UName:(NSString*)uname;
//进入聊天室
- (long) enterRoom; // enter the room

//
- (long) leaveRoom;

//说话，发消息
- (long) speak:(NSString*) message to:(NSString*)uid ispublic:(bool)isall;     // speak in the room, include

- (void) userList;

//设置消息接受者，任意改变
- (void)setReceiverObject:(id<OnChatDelegate>)delegate;



@end










