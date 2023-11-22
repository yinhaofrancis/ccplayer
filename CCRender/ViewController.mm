//
//  ViewController.m
//  CCRender
//
//  Created by wenyang on 2023/11/13.
//

#import "ViewController.h"
//#include "GL/cc_render_es1.hpp"
#include "codec.hpp"
#include "GL/cc_render.hpp"
#include "audio_queue.hpp"
#import "CCRenderUIkit.h"
//#import <AVFoundation/AVFoundation.h>
#import <objc/runtime.h>
#import <objc/message.h>
@interface ViewController (){
    cc::player * c;
    
    EAGLContext *ctx;

    CCRenderUIkit* render;
}

//@property(atomic,assign) cc::render *ctx3;
@property(atomic,assign) uint8_t angle;
@end

@implementation ViewController



- (void)viewDidLoad {
    [super viewDidLoad];
    
//
    auto a = [NSBundle.mainBundle URLForResource:@"b" withExtension:@"mp4"].path.UTF8String;
    
    
//    auto a = "/Users/haoyin/Desktop/a.mp4";

    

    
    id  sharedObject = [objc_lookUpClass("AVAudioSession") performSelector:sel_getUid("sharedInstance")];
    [sharedObject performSelector:sel_getUid("setActive:error:") withObject:@true withObject:nil];
    
    c = new cc::player(a);
    
    c->play();
//    __weak ViewController * ws = self;
//    render = [[CCRenderUIkit alloc] initWithCallBack:^{

//    }];
    render = [[CCRenderUIkit alloc] initWithTarget:self selector:@selector(renderAction:)];
    [self.view.layer addSublayer:render.layer];
    render.layer.frame = CGRectMake(0, 0, 320, 567);
    c->video_render().setScreen(320, 567);

//    vp = new media::VideoPlayer(a);
//    vp->play();
//    
    
}
- (void)renderAction:(NSNumber*)framebf{
        auto frame = self->c->get_current_frame();
        if(frame == nullptr){
            return;
        }
//        self->c->video_render().render(frame,framebf.intValue);
        av_frame_free(&frame);
}
- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
//    c->pause();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect{

//    

    
//    if (self->aq->is_pendding()) return;
    
    int w = rect.size.width * self.view.layer.contentsScale;
    int h = rect.size.height * self.view.layer.contentsScale;
    if(self.view.window == nil){
        [render stop];
    }
}
- (void)dealloc
{
    delete c;
    
}


@end


