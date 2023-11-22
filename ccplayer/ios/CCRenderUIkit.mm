//
//  CCRenderUIkit.m
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#import "CCRenderUIkit.h"
//#include "codec.hpp"
@interface  CCEAGLRender()
@property(nonatomic,strong) NSThread *thread;
@property(nonatomic,strong) CADisplayLink *link;
@property(nonatomic,strong) NSRunLoop *runloop;
@property(nonatomic,assign) GLuint colorRendrBuffer;
@property(nonatomic,assign) GLuint depthRendrBuffer;
@property(nonatomic,assign) GLuint stencilRendrBuffer;
@property(nonatomic,assign) GLuint frameBuffer;
@property(nonatomic,  copy) void(^ callback)(void);
@end

@implementation CCEAGLRender

- (instancetype)initWithTarget:(id)target selector:(SEL)selector{
    __weak CCEAGLRender* c = self;
    __weak id wt = target;
    return [self initWithCallback:^{
        if(c == nil){
            return;
        }
        [wt performSelector:selector withObject:@(c.frameBuffer)];
    }];
}

- (instancetype)initWithCallback:(void(^)(void))callback
{
    self = [super init];
    if (self) {
        self.callback = callback;
        __weak CCEAGLRender* ws = self;
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
    _callback();
    [self.context presentRenderbuffer:GL_RENDERBUFFER];
}
- (void)stop{
    [self.link removeFromRunLoop:self.runloop forMode:NSDefaultRunLoopMode];
    [self.link invalidate];
    self.link = nil;
    _callback = nil;
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

@end
