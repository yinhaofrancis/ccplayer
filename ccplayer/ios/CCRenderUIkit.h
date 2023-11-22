//
//  CCRenderUIkit.h
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <OpenGLES/EAGL.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

NS_ASSUME_NONNULL_BEGIN

@interface CCEAGLRender : NSObject

@property(nonatomic,readonly) CAEAGLLayer *layer;

@property(nonatomic,readonly) EAGLContext *context;


@property(nonatomic,readonly)int width;

@property(nonatomic,readonly)int height;



- (instancetype)initWithTarget:(id)target selector:(SEL)selector;

- (void)stop;

@end

NS_ASSUME_NONNULL_END
