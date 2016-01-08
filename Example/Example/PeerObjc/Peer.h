//
//  Peer.h
//  PeerObjc
//
//  Created by zhubch on 15-3-6.
//  Copyright (c) 2015年 zhubch. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SRWebSocket.h"
#import "DataConnection.h"
#import "MediaConnection.h"

/**
 *  代表一个端
 */
@interface Peer : NSObject

/**
 *  端的唯一标识
 */
@property(nonatomic, strong) NSString   *peerId;

/**
 *  peer正常打开的回调
 */
@property(nonatomic, copy) void(^onOpen)(NSString *peerId);

/**
 *  peer收到连接时的回调
 */
@property(nonatomic, copy) void(^onConnection)(Connection *connection);

/**
 *  被关闭时的回调
 */
@property(nonatomic, copy) void(^onClose)();

/**
 *  出错时的回调
 */
@property(nonatomic, copy) void(^onError)(NSError *error);

/**
 *  状态标记
 */
@property(nonatomic, assign) BOOL        open;

/**
 *  socket
 */
@property(nonatomic, strong, readonly) SRWebSocket *webSock;

@property(nonatomic, strong, readonly) NSArray    *iceServers;

- (id)init __attribute__((unavailable("not avaliable")));

/**
 *  实例化
 *
 *  @param peerId  可以自己设定，也可以为空，自己设定的时候千万不要分配给两个peer一样的ID。
 *  @param options 可以自己设定，也可以为空，自己设定时应按照以下格式：
 *                                @{
 *                                  @"host":kDefaultHost,
                                    @"path":kDefaultPath,
                                    @"key":kDefaultKey,
                                    @"secure":@(NO),
                                    @"config":@{
                                                @"iceServers":@[
                                                                @{
                                                                    @"url":kDefaultSTUNServerUrl,
                                                                    @"username":@"",
                                                                    @"credential":@""
                                                                    }
                                                                ]
                                                }
                                    };
 *
 *  @return Peer
 */
- (instancetype)initWithPeerId:(NSString*)peerId options:(NSDictionary*)options;

/**
 *  向其它peer对象发起连接
 *
 *  @param peerId  目标的peerID
 *  @param options 附加信息
 *
 *  @return 数据连接对象
 */
- (DataConnection*)connectToPeer:(NSString*)peerId options:(NSDictionary*)options;

- (MediaConnection*)callPeer:(NSString*)peerId options:(NSDictionary*)options;

- (void)disconnectAllConnections;

- (void)disconnect:(Connection*)connection;

- (void)cleanUp;

@end
