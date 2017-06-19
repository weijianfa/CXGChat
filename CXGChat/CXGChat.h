//
//  CXGChat.h
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/17.
//  Eidt by Li xinhang on 2017/07/11.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for CXGChat.
FOUNDATION_EXPORT double CXGChatVersionNumber;

//! Project version string for CXGChat.
FOUNDATION_EXPORT const unsigned char CXGChatVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <CXGChat/PublicHeader.h>

@interface EntryAnimation : NSObject
{
    bool _isShow;
    
    NSInteger _ID;
    NSString* _path;
    NSString* _version;
}

- (bool) isShow;

- (NSInteger) getID;
- (NSString*) getPath;
- (NSString*) getVersion;

- (void) setProPertyWithID:(NSInteger)ID andPath:(NSString*)path andVersion:(NSString*)version isShow:(bool)isShow;
@end


@interface User : NSObject
{
    NSString* userID;
    NSString* nickName;
    NSString* headIcon;
    NSString* gameUid;
    
    NSString* roomRole;
    NSString* gameZoneName;
    
    NSInteger terminal;
    NSInteger userType;
    NSInteger roleID;
    NSInteger sortNum;
    
    NSInteger fansLevel;
    NSInteger richLevel;
    NSInteger userLevel;
    
    NSInteger equipScore;
    NSInteger gameRoleType;
    NSInteger gameVIPLevel;
    
    bool isAnchor;
    bool isReconnect;
    bool isAllowPrivateChat;
}

@property EntryAnimation* entryAnimation;
- (EntryAnimation*) getEntryAnimation;

- (id) init;

- (NSString*) getUserID;
- (NSString*) getNickName;
- (NSString*) getHeadIcon;
- (NSString*) getGameUid;

- (NSString*) getRoomRole;
- (NSString*) getGameZoneName;

- (NSInteger) getTerminal;
- (NSInteger) getUserType;
- (NSInteger) getRoleID;
- (NSInteger) getSortNum;

- (NSInteger) getFansLevel;   //getfansLevel
- (NSInteger) getRichLevel;   //getRichLevel
- (NSInteger) getUserLevel;   //getuserLevel

- (NSInteger) getEquipScore;
- (NSInteger) getGameRoleType;
- (NSInteger) getGameVIPLevel;

//- (bool) isAnchor;
- (bool) getReconnectStatus;
- (bool) getPrivateChatStatus;


- (void) setUserBaseInfoWithUid:(NSString*) uid andNickName:(NSString*) name andHeadIcon:(NSString*) icon andGameUid:(NSString*) guid;
- (void) setUserDetailInfoWithRoomRole:(NSString*) role andUserType:(NSInteger) type andRoleID:(NSInteger) roleid andSortNum:(NSInteger) num;
- (void) setUserGameInfoWithGameZoneName:(NSString*) zonename andEquipScore:(NSInteger) score andGameRoleType:(NSInteger) gameroletype andGameVipLevel:(NSInteger) viplevel;
- (void) setUserLevelInfoWithFans:(NSInteger) fanslv andRich:(NSInteger) richlv andUser:(NSInteger) userlv;

- (void) setTerminal:(NSInteger) term;
- (void) setPrivateChatStatus:(bool) isallow;
- (void) setReconnectStatus:(bool) isreconnect;
@end


@interface Gift : NSObject
{
    NSString* giftName;
    NSString* giftIcon;
    NSString* giftUniqueID;
    
    NSInteger giftID;
    NSInteger giftCount;
    NSInteger giftType;
    NSInteger comboNum;
    NSInteger comboGroupNum;
    NSInteger version;
    
    bool _isAutoCombo;
    bool _isCombo;
    bool _isFree;
}

- (NSString*) getGiftName;
- (NSString*) getGiftIcon;
- (NSString*) getGiftUniqueID;

- (NSInteger) getGiftID;
- (NSInteger) getGiftCount;
- (NSInteger) getGiftType;
- (NSInteger) getComboNum;
- (NSInteger) getComboGroupNum;
- (NSInteger) getVersion;

- (bool) isAutoCombo;
- (bool) isCombo;
- (bool) isFree;

- (void) setGiftBaseInfoWithName:(NSString*)name andID:(NSInteger)giftid andIcon:(NSString*)icon;
- (void) setGiftDetailInfoWithUniqueID:(NSString*)uniqueid andCount:(NSInteger)count andType:(NSInteger)type andFree:(bool)isfree;
- (void) setGiftComboInfoWithAutoCombo:(bool)isauto andCombo:(bool)iscommbo andComboNum:(NSInteger)num andGroupNum:(NSInteger)groupnum;
- (void) setGiftVersion:(NSInteger)ver;
@end


@interface Message : NSObject
{
    NSInteger mType;
    NSInteger mSubType;
    
    NSString* message;
    NSInteger mExtraProperty;
}

@property Gift* Gift;
@property User* User;
@property User* receiveUser;
@property NSMutableArray* UserList;

- (id) init;

- (NSString*) getMsg;
- (NSInteger) getType;
- (NSInteger) getSubType;
- (NSInteger) getExtraProperty;

- (User*) getUser;
- (User*) getReceiveUser;
- (Gift*) getGift;
- (NSMutableArray*) getUserList;

- (void) setMsgBaseInfoWithType:(NSInteger)type andSubType:(NSInteger)subtype andContent:(NSString*) msg;
- (void) setMsgExtraInfo:(NSInteger)extraProperty;
- (void) addUserIntoList:(User*)user;
@end


@protocol OnChatDelegate <NSObject>
- (void)onMessage:(Message*) package;
- (void)onError:(long) andErrorCode Msg:(NSString*) msg;
@end


@interface ChatInterface : NSObject

- (void) setRoomWithHost:(NSString*)host andPort:(int)port andUserID:(NSString*)uid andRoomID:(NSString*)rid;
- (void) setToken:(NSString*) token;

- (long) enterChatRoom;
- (void) leaveChatRoom;

- (void) speak:(NSString*)message to:(NSString*)uid andPrivate:(bool)isprivate;     // speak in the room, include
- (void) getUserList;  //上层还完全没写

- (void) setReceiverObject:(id<OnChatDelegate>)delegate;
@end










