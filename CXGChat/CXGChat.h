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





@interface ChatInterface : NSObject {
    long mUid;    // user id
    NSString* mToken;  // login key
    long mRid;    // room id
    NSString* mUname;  // nick name
    int mPort;
    
    NSString* mHost;    // server config
}

- (void) setHost:(NSString *)host;
- (void) setPort:(int) port;
- (void) setUid:(long )uid;
- (void) setToken:(NSString *)token;
- (void) setRid:(long)rid;
- (void) setUname:(NSString *) uname;

- (int) enterRoom;

@end


