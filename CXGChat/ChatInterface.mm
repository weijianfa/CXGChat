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


@implementation ChatInterface

- (void) setHost:(NSString *)host {
    mHost = host;
}

- (void) setUid:(long)uid {
    mUid = uid;
}

- (void) setToken:(NSString *)token {
    mToken = token;
}

- (void) setRid:(long)rid {
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
    manager->setUser(mUid, mRid, [mToken UTF8String]);
    
    manager->Enter();

    return 1;
}

@end
