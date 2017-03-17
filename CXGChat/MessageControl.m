//
//  MessageControl.m
//  CXGChat
//
//  Created by Lu Jinfei on 2017/3/5.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

//#import <Foundation/Foundation.h>



#import "MessageControl.h"


@interface ChatControl (){
    
    dispatch_queue_t chatQueue;
}



@end


@implementation ChatControl


- (void)dealloc
{
    
}

- (id)init
{
    if (self = [super init]) {
        
        
        chatQueue = dispatch_queue_create([@"ShowRoom" UTF8String], DISPATCH_QUEUE_SERIAL);
        

    }
    
    return self;

}

- (void) doOnMessage :(Message*) pkg{
    
    dispatch_async(chatQueue, ^{
        
        if (_delegate && [_delegate respondsToSelector:@selector(onMessage:)]) {
            [self.delegate onMessage:pkg];
        }
        
    });

}

- (void) doOnError :(int) errorCode Msg:(NSString*) msg{
    
    dispatch_async(chatQueue, ^{
        if (_delegate && [_delegate respondsToSelector:@selector(onError:Msg:)]) {
            [self.delegate onError:errorCode Msg:msg];
        }
    });
    
    
   
    
}

@end
