//
//  CCRenderUIkit.m
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//
#import <OpenGLES/EAGL.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>

#include "../player/player.hpp"
#import "CCPlayer.h"
#include "../render/video.hpp"

@interface  CCPlayer(){
    cc::player* player;
    cc::video_display video;
}@property(nonatomic,strong) NSThread *thread;

@property(nonatomic,strong) CADisplayLink *link;

@property(nonatomic,strong) NSRunLoop *runloop;

@property(nonatomic,assign) GLuint colorRendrBuffer;
@property(nonatomic,assign) GLuint depthRendrBuffer;
@property(nonatomic,assign) GLuint stencilRendrBuffer;
@property(nonatomic,assign) GLuint frameBuffer;

@property(nonatomic,readonly)int width;

@property(nonatomic,readonly)int height;

@end

@implementation CCPlayer

- (instancetype)initWithUrl:(NSURL *)url{
    self = [super init];
    if (self) {
        auto a = url.scheme.length > 0 ? url.absoluteString.UTF8String : url.path.UTF8String;
        try {
            player = new cc::player(a);
            player->play();
        } catch (cc::error) {
            return nil;
        }
        
        __weak CCPlayer* ws = self;
        player->time_callback() = [ws](auto current,auto duaration){
            __strong CCPlayer* sws = ws;
            dispatch_async(dispatch_get_main_queue(), ^{
                if(sws.observerTime != nil ){
                    sws.observerTime(duaration == 0 ?  0.0 : current / duaration);
                }
            });
        };
        
        
        _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
        _layer = [[CAEAGLLayer alloc] init];
        _layer.contentsScale = 3;
        _layer.opaque = true;
        _layer.frame = CGRectMake(0, 0, 100, 100);
        _layer.drawableProperties =  @{
            kEAGLDrawablePropertyColorFormat:kEAGLColorFormatRGBA8,
            kEAGLDrawablePropertyRetainedBacking:@(false)
        };
 
        
        self.thread = [[NSThread alloc] initWithBlock:^{
            
            ws.runloop = NSRunLoop.currentRunLoop;
            CADisplayLink* link = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawCall)];
            [link addToRunLoop:ws.runloop forMode:NSDefaultRunLoopMode];
            ws.link = link;
            [ws.runloop run];
        }];
        [self.thread start];
        
   
        
    }
    return self;
}

- (void)dealloc
{
    glDeleteFramebuffers(1, &_frameBuffer);
    GLuint m [3] = {_colorRendrBuffer,_depthRendrBuffer,_stencilRendrBuffer};
    glDeleteRenderbuffers(3, m);
}
-(void)draw{
    video.setScreen(self.width, self.height);
    auto frame = player->get_current_frame();
    video.render(frame);
}
- (void)drawCall{
    [EAGLContext setCurrentContext:self.context];
    self.context.debugLabel = @"vvvv";
    if(_frameBuffer == 0){
        glGenRenderbuffers(1, &_colorRendrBuffer);
        glGenRenderbuffers(1, &_depthRendrBuffer);
        glGenRenderbuffers(1, &_stencilRendrBuffer);
        glGenFramebuffers(1, &_frameBuffer);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, self.frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, self.colorRendrBuffer);
    [self.context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_layer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRendrBuffer);

    GLsizei width = 0;
    GLsizei height = 0;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
    
    
    
//    glBindRenderbuffer(GL_RENDERBUFFER, self.depthRendrBuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width, height);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRendrBuffer);
    
    
    glBindRenderbuffer(GL_RENDERBUFFER, self.stencilRendrBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _stencilRendrBuffer);
   
    
    
    glBindRenderbuffer(GL_RENDERBUFFER, self.colorRendrBuffer);
    
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        // 处理帧缓存不完整的情况
        NSLog(@"%X",status);
    }
    [self draw];
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}
- (void)stop{
    delete player;
    [self.link removeFromRunLoop:self.runloop forMode:NSDefaultRunLoopMode];
    [self.link invalidate];
    self.link = nil;
    self.observerTime = nil;
    CFRunLoopStop([_runloop getCFRunLoop]);
    [_thread cancel];
}

- (int)width{
    int size = 0;
    glBindFramebuffer(GLenum(GL_FRAMEBUFFER), _frameBuffer);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &size);
    return size;
}
- (int)height{
    int size = 0;
    glBindFramebuffer(GLenum(GL_FRAMEBUFFER), _frameBuffer);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &size);
    return size;
}

- (void)seek:(double)percent{
    self->player->seek_to(percent);
}
- (void)play{
    self->player->play();
}
- (void)pause{
    self->player->pause();
}
- (player_state)state{
    return self->player->state();
}
- (void)rate:(double)rate {
    self->player->rate(rate);
}

@end
