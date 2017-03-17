//
//  MessageControl.h
//  CXGChat
//
//  Created by hehe on 2017/3/17.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//


#import "CXGChat.h"


@interface ChatControl : NSObject
//遵循协议的一个代理变量定义
@property (nonatomic, weak) id<OnChatDelegate> delegate;
- (void) doOnMessage:(Message*) pkg;
- (void) doOnError:(int) errorCode Msg:(NSString*) msg;
@end
