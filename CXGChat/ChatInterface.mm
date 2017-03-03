//
//  ChatInterface.m
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/22.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CXGChat.h"
#import "ChatManager.hpp"

@implementation Message

- (void) setUid:(NSString*) uid {
    mUid = uid;
}
- (void) setNickName:(NSString*) name {
    mNickName = name;
}
- (void) setMsg:(NSString*) msg {
    mMsg = msg;
}

- (NSString*) getUid {
    return mUid;
}
- (NSString*) getNickName {
    return mNickName;
}
- (NSString*) getMsg {
    return mMsg;
}

@end

@implementation MsgListener
-(void) OnMsg:(Message*) pkg {
    
}
-(void) OnError:(int) errorCode Msg:(NSString*) msg {
    
}

@end


@implementation ChatInterface

- (void) setHost:(NSString *)host {
    mHost = host;
}

- (void) setUid:(NSString *)uid {
    mUid = uid;
}

- (void) setToken:(NSString *)token {
    mToken = token;
}

- (void) setRid:(NSString *)rid {
    mRid= rid;
}

- (void) setUname:(NSString *) uname {
    mUname = uname;
}

- (void) setPort:(int)port{
    mPort = port;
}

- (int) enterRoom {
    
    ChatManager* manager = new ChatManager([mHost UTF8String], mPort);
    manager->setUser([mUid UTF8String], [mRid UTF8String], [mToken UTF8String]);
    manager->setListner(mListener);
    manager->Enter();


    return 1;
}

- (void) setListener:(MsgListener *)listener {
    mListener = listener;
}

@end
