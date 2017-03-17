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

@interface Message : NSObject {
    NSString* mUid;
    NSString* mNickName;
    NSString* mMsg;
}

- (void) setUid:(NSString*) uid;
- (void) setNickName:(NSString*) name;
- (void) setMsg:(NSString*) msg;

- (NSString*) getUid;
- (NSString*) getNickName;
- (NSString*) getMsg;

@end



@protocol OnChatDelegate <NSObject>
- (void)onMessage:(Message*) pkg;
- (void)onError:(int) errorCode Msg:(NSString*) msg;
@end



@interface ChatInterface : NSObject

//配置chat服务器地址
- (void)configureRoomHost:(NSString*)host Port:(int)port UID:(NSString*)uid Token:(NSString*)t Rid:(NSString*)rid UName:(NSString*)uname;
//进入聊天室
- (int) enterRoom; // enter the room

//说话，发消息
- (int) speak:(NSString*) message to:(NSString*)uid ispublic:(bool)isall;     // speak in the room, include

//设置消息接受者，任意改变
- (void)setReceiverObject:(id<OnChatDelegate>)delegate;








@end










