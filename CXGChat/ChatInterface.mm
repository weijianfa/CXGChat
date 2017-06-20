//
//  ChatInterface.m
//  CXGChat
//
//  Created by Lu Jinfei on 2017/2/22.
//  Copyright © 2017年 Lu Jinfei. All rights reserved.
//

#import "CXGChat.h"
#import "ChatManager.hpp"
#import "MessageControl.h"

@implementation EntryAnimation

- (bool) isShow{
    return _isShow;
}
- (NSInteger) getID{
    return _ID;
}
- (NSString*) getPath{
    return _path;
}
- (NSString*) getVersion{
    return _version;
}

- (void) setProPertyWithID:(NSInteger)ID andPath:(NSString *)path andVersion:(NSString *)version isShow:(bool)isShow
{
    _ID = ID;
    _path = path;
    _version = version;
    _isShow = isShow;
}
@end


@implementation User

- (NSString*) getUserID{
    return userID;
}
- (NSString*) getNickName{
    return nickName;
}
- (NSString*) getHeadIcon{
    return headIcon;
}
- (NSString *)getGameUid{
    return gameUid;
}

- (NSString*) getRoomRole{
    return roomRole;
}
- (NSString*) getGameZoneName{
    return gameZoneName;
}


- (NSInteger) getTerminal{
    return terminal;
}
- (NSInteger) getUserType{
    return userType;
}
- (NSInteger) getRoleID{
    return roleID;
}
- (NSInteger) getSortNum{
    return sortNum;
}

- (NSInteger) getFansLevel{
    return fansLevel;
}
- (NSInteger) getRichLevel{
    return richLevel;
}
- (NSInteger) getUserLevel{
    return userLevel;
}


- (NSInteger) getEquipScore{
    return equipScore;
}
- (NSInteger) getGameRoleType{
    return gameRoleType;
}
- (NSInteger) getGameVIPLevel{
    return gameVIPLevel;
}

- (bool) getPrivateChatStatus{
    return isAllowPrivateChat;
}
- (bool) getReconnectStatus{
    return isReconnect;
}

- (EntryAnimation*) getEntryAnimation{
    return _entryAnimation;
}

- (id) init
{
    self = [super init];
    if(self)
        _entryAnimation = [[EntryAnimation alloc] init];
    
    return self;
}


- (void) setUserBaseInfoWithUid:(NSString *)uid andNickName:(NSString *)name andHeadIcon:(NSString *)icon andGameUid:(NSString *)guid
{
    userID = uid;
    nickName = name;
    headIcon = icon;
    gameUid = guid;
}

- (void) setUserLevelInfoWithFans:(NSInteger)fanslv andRich:(NSInteger)richlv andUser:(NSInteger)userlv
{
    fansLevel = fanslv;
    richLevel = richlv;
    userLevel = userlv;
}

- (void) setUserDetailInfoWithRoomRole:(NSString *)role andUserType:(NSInteger)type andRoleID:(NSInteger)roleid andSortNum:(NSInteger)num
{
    roomRole = role;
    userType = type;
    roleID = roleid;
    sortNum = num;
}

- (void) setUserGameInfoWithGameZoneName:(NSString *)zonename andEquipScore:(NSInteger)score andGameRoleType:(NSInteger)gameroletype andGameVipLevel:(NSInteger)viplevel
{
    gameZoneName = zonename;
    equipScore = score;
    gameRoleType = gameroletype;
    gameVIPLevel = viplevel;
}

- (void) setTerminal:(NSInteger)term
{
    terminal = term;
}

- (void) setPrivateChatStatus:(bool)isallow
{
    isAllowPrivateChat = isallow;
}

- (void) setReconnectStatus:(bool)isreconnect
{
    isReconnect = isreconnect;
}
@end


@implementation  Gift

- (NSString*) getGiftName{
    return giftName;
}
- (NSString*) getGiftIcon{
    return giftIcon;
}
- (NSString*) getGiftUniqueID{
    return giftUniqueID;
}

- (NSInteger) getGiftID{
    return giftID;
}
- (NSInteger) getGiftCount{
    return giftCount;
}
- (NSInteger) getGiftType{
    return giftType;
}
- (NSInteger) getComboNum{
    return comboNum;
}
- (NSInteger) getComboGroupNum{
    return comboGroupNum;
}
- (NSInteger) getVersion{
    return version;
}

- (bool) isCombo{
    return _isCombo;
}
- (bool) isAutoCombo{
    return _isAutoCombo;
}
- (bool) isFree{
    return _isFree;
}

- (void) setGiftBaseInfoWithName:(NSString *)name andID:(NSInteger)giftid andIcon:(NSString *)icon
{
    giftName = name;
    giftID = giftid;
    giftIcon = icon;
}

- (void) setGiftDetailInfoWithUniqueID:(NSString *)uniqueid andCount:(NSInteger)count andType:(NSInteger)type andFree:(bool)isfree
{
    giftUniqueID = uniqueid;
    giftCount = count;
    giftType = type;
}

- (void) setGiftComboInfoWithAutoCombo:(bool)isauto andCombo:(bool)iscombo andComboNum:(NSInteger)num andGroupNum:(NSInteger)groupnum
{
    _isAutoCombo = isauto;
    _isCombo = iscombo;
    comboNum = num;
    comboGroupNum = groupnum;
}

- (void) setGiftVersion:(NSInteger)ver
{
    version = ver;
}
@end

@implementation Message

- (NSInteger) getType{
    return mType;
}
- (NSInteger) getSubType{
    return mSubType;
}
- (NSInteger) getExtraProperty{
    return mExtraProperty;
}

- (NSString*) getMsg{
    return message;
}
- (User*) getUser{
    return _User;
}
- (User*) getReceiveUser{
    return _receiveUser;
}
- (Gift*) getGift {
    return _Gift;
}
- (NSMutableArray*) getUserList {
    return _UserList;
}

- (id) init
{
    self = [super init];
    if(self)
    {
        if(_UserList == NULL)
            _UserList = [[NSMutableArray alloc] init];
        
        _User = [[User alloc] init];
        _Gift = [[Gift alloc] init];
        _receiveUser = [[User alloc] init];
    }
    
    return self; 
}

- (void) setMsgBaseInfoWithType:(NSInteger)type andSubType:(NSInteger)subtype andContent:(NSString *)msg
{
    mType = type;
    mSubType = subtype;
    message = msg;
}

- (void) setMsgExtraInfo:(NSInteger)extraProperty
{
    mExtraProperty = extraProperty;
}

- (void) addUserIntoList:(User*)user
{
    [_UserList addObject:user];
}
@end


@interface ChatInterface ()

@property (nonatomic,strong)NSString* Uid;
@property (nonatomic,strong)NSString* Rid;
@property (nonatomic,assign)NSString* Host;
@property (nonatomic,strong)NSString* Token;
@property (nonatomic,assign)int Port;

@property (nonatomic,strong)ChatControl* Controller; //

@end


@implementation ChatInterface

- (void)dealloc{
    _Controller = nil;
}

- (void) setRoomWithHost:(NSString *)host andPort:(int)port andUserID:(NSString *)uid andRoomID:(NSString *)rid
{
    _Host = host;
    _Port = port;
    
    _Uid = uid;
    _Rid = rid;
    
    if(!_Controller)
        _Controller = [[ChatControl alloc] init];
}

- (void) setToken:(NSString *)token
{
    _Token = token;
}


- (long) enterChatRoom
{
    NSString* resources = [[NSBundle mainBundle] resourcePath];
    NSString *path = [NSString stringWithFormat:@"%s/locale/", [resources cStringUsingEncoding:NSUTF8StringEncoding]] ;
    setenv( "PATH_LOCALE", [path UTF8String] ,1);
    setlocale(LC_CTYPE, "zh_CN.UTF-8");
    
    
    ChatManager* manager = ChatManager::GetInstance();
    manager->setHost([_Host UTF8String], _Port);
    manager->setUser([_Uid UTF8String], [_Rid UTF8String]);
    manager->setToken([_Token UTF8String]);
    manager->setController(_Controller);
    manager->EnterChatRoom();

    return 1;
}

- (void) leaveChatRoom
{
    ChatManager* manager = ChatManager::GetInstance();
    manager->ExitChatRoom();
}

- (void) speak:(NSString*) message to:(NSString*)uid andPrivate:(bool)isprivate
{
    ChatManager* manager = ChatManager::GetInstance();
    manager->SendChatMsg([message UTF8String], [uid UTF8String], isprivate);
}

- (void) requestUserInfoWith:(NSString*)uid andVersion:(NSInteger)version
{
    ChatManager* manager = ChatManager::GetInstance();
    manager->RequestUserInfo([uid UTF8String],version);
}

- (void) requestUserListWith:(NSInteger)pageno andMaxNum:(NSInteger)maxnum andVersion:(NSInteger)version
{
    ChatManager* manager = ChatManager::GetInstance();
    manager->RequestUserList(pageno, maxnum, version);
}

- (void)setReceiverObject:(id<OnChatDelegate>)delegate
{
    _Controller.delegate = delegate;
}

@end
