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
#import "MessageControl.h"


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

- (void) setType:(NSInteger) type {
    mType = type;
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
- (NSInteger) getType {
    return mType;
}

- (User*) getUser {
    return mUser;
}

- (Gift*) getGift {
    return mGift;
}

- (id) init
{
    if(self = [super init])
    {
        mUser = [[User alloc] init];
        mGift = [[Gift alloc] init];
    }
    return self; 
}

@end


@implementation User

- (NSInteger) getFensi {
    return fensi;
}

- (NSInteger) getCaifu {
    return caifu;
}

- (NSInteger) getJuese {
    return juese;
}

- (void) setFensi:(NSInteger) temp {
    self->fensi = temp;
}

- (void) setCaifu:(NSInteger) temp {
    self->caifu = temp;
}

- (void) setJuese:(NSInteger) temp {
    self->juese = temp;
}

@end

@implementation  Gift

- (NSString*) getName {
    return name;
}
- (NSInteger) getCount {
    return count;
}

- (void) setName:(NSString*) temp {
    self->name = temp;
}

- (void) setCount:(NSInteger) temp {
    self->count = temp;
}

@end




@interface ChatInterface ()

@property (nonatomic,strong)NSString* mUid;    // user id
@property (nonatomic,strong)NSString* mToken;    // user id

@property (nonatomic,strong)NSString* mRid;    // user id

@property (nonatomic,strong)NSString* mUname;    // user id

@property (nonatomic,assign)long mPort;    // user id
@property (nonatomic,assign)NSString* mHost;   // user id

@property (nonatomic,strong)    ChatControl* mController; //



@end


@implementation ChatInterface

- (void)dealloc
{
    _mController = nil;
}


- (void)configureRoomHost:(NSString*)host Port:(int)port UID:(NSString*)uid Token:(NSString*)t Rid:(NSString*)rid UName:(NSString*)uname
{
    if ([host length]) {
        _mHost = host;
    }
    if (port != 0) {
        _mPort = port;
    }
    if ([uid length]) {
        _mUid = uid;

    }
    if ([t length]) {
        _mToken = t;

    }
    
    if ([rid length]) {
        _mRid = rid;

    }
    
    if ([uname length]) {
        _mUname = uname;

    }
    
    if (!_mController) {
        _mController = [[ChatControl alloc] init];
        
    }
    
    
}


- (int) enterRoom {
    NSString* resources = [[NSBundle mainBundle] resourcePath];
    NSString *s = [NSString stringWithFormat:@"%s/locale/", [resources cStringUsingEncoding:NSUTF8StringEncoding]] ;
    setenv( "PATH_LOCALE", [s UTF8String] ,1);
    
    
    ChatManager* manager = ChatManager::GetInstance();
    manager->setHost([_mHost UTF8String], _mPort);
    manager->setUser([_mUid UTF8String], [_mRid UTF8String], [_mToken UTF8String]);
    manager->setController(_mController);
    manager->Enter();

    return 1;
}

- (int) leaveRoom {
    ChatManager* manager = ChatManager::GetInstance();
    manager->ExitChatRoom();
    return 1;
}

- (int) speak:(NSString*) message to:(NSString*)uid ispublic:(bool)isall {
    ChatManager* manager = ChatManager::GetInstance();
    manager->Speak([message UTF8String], [uid UTF8String], isall);
    return 1;
}



- (void)setReceiverObject:(id<OnChatDelegate>)delegate
{
    _mController.delegate = delegate;
}


@end
