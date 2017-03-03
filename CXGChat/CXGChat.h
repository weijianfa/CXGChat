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




@interface MsgListener : NSObject

-(void) OnMsg:(Message*) pkg;
-(void) OnError:(int) errorCode Msg:(NSString*) msg;

@end



@interface ChatInterface : NSObject {
    NSString* mUid;    // user id
    NSString* mToken;  // login key
    NSString* mRid;    // room id
    NSString* mUname;  // nick name
    int mPort;
    
    NSString* mHost;    // server config
    
    MsgListener* mListener; //
}

- (void) setHost:(NSString *)host;
- (void) setPort:(int) port;
- (void) setUid:(NSString * )uid;
- (void) setToken:(NSString *)token;
- (void) setRid:(NSString *)rid;
- (void) setUname:(NSString *) uname;
- (void) setListener:(MsgListener*) listener;

- (int) enterRoom;

@end










