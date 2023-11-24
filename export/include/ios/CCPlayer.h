//
//  CCPlayer.h
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import "type/type.h"


NS_ASSUME_NONNULL_BEGIN

@interface CCPlayer : NSObject

@property(nonatomic,readonly) CAEAGLLayer *layer;

@property(nonatomic,readonly) EAGLContext *context;

@property(nonatomic,readonly) enum player_state state;

@property(nullable,  copy) void(^ observerTime)(double);

- (instancetype)initWithUrl:(NSURL *)url;

- (void)stop;

- (void)pause;

- (void)play;

- (void)seek:(double)percent;

- (void)rate:(double)rate;


@end

NS_ASSUME_NONNULL_END
