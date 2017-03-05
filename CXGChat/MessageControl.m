//
//  MessageControl.m
//  CXGChat
//
//  Created by Lu Jinfei on 2017/3/5.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

//#import <Foundation/Foundation.h>
#import "CXGChat.h"

@implementation ChatControl

- (void) doOnMessage :(Message*) pkg{
    [self.delegate onMessage:pkg];
}

- (void) doOnError :(int) errorCode Msg:(NSString*) msg{
    [self.delegate onError:errorCode Msg:msg];
}

@end
