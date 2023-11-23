//
//  iewController.m
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#import "iewController.h"
#include "player.hpp"
#include "video.hpp"
#import "CCRenderUIkit.h"
#import <objc/runtime.h>
#import <objc/message.h>
#import <MobileCoreServices/MobileCoreServices.h>
@interface iewController (){

    cc::player* player;
    cc::video_display video;
}

@end

@implementation iewController

- (void)viewDidLoad {
    [super viewDidLoad];
    id  sharedObject = [objc_lookUpClass("AVAudioSession") performSelector:sel_getUid("sharedInstance")];
        [sharedObject performSelector:sel_getUid("setActive:error:") withObject:@true withObject:nil];
    auto a = _u.path.UTF8String;
//    auto a = "/Users/haoyin/Desktop/gamesci_2022PV03.mp4";
    player = new cc::player(a);
    player->play();
    
//    _player->play();
    self.render = [[CCEAGLRender alloc] initWithTarget:self selector:@selector(call:)];
    [self.view.layer addSublayer:self.render.layer];
    self.render.layer.frame = CGRectMake(0, 0, 414, 414.0 * 16 / 9);
    

    UIButton* b = [UIButton buttonWithType:UIButtonTypeSystem];
    b.frame = CGRectMake(0, 88, 88, 88);
    [b addTarget:self action:@selector(pause) forControlEvents:UIControlEventTouchUpInside];
    [b setTitle:@"暂停" forState:UIControlStateNormal];
    b.tintColor = UIColor.cyanColor;
    [self.view addSubview:b];
    
    
    UIButton* c = [UIButton buttonWithType:UIButtonTypeSystem];
    c.frame = CGRectMake(88, 88, 88, 88);
    [c addTarget:self action:@selector(play) forControlEvents:UIControlEventTouchUpInside];
    [c setTitle:@"播放" forState:UIControlStateNormal];
    c.tintColor = UIColor.cyanColor;
    [self.view addSubview:c];
    
    UISlider *d = [[UISlider alloc] init];
    [self.view addSubview:d];
    d.maximumValue = 1;
    d.minimumValue = 0;
    d.frame = CGRectMake(88, 88 + 88, 300,44);
    [d addTarget:self action:@selector(slider:) forControlEvents:UIControlEventValueChanged];
    
    [d addTarget:self action:@selector(sliderEnd:) forControlEvents:UIControlEventTouchUpInside];
//    d.continuous = false;
    {
        UIButton* c = [UIButton buttonWithType:UIButtonTypeSystem];
        c.frame = CGRectMake(88 + 88, 88, 88, 88);
        [c addTarget:self action:@selector(playp5) forControlEvents:UIControlEventTouchUpInside];
        [c setTitle:@"0.75x" forState:UIControlStateNormal];
        c.tintColor = UIColor.cyanColor;
        [self.view addSubview:c];
    }
    
    {
        UIButton* c = [UIButton buttonWithType:UIButtonTypeSystem];
        c.frame = CGRectMake(88 + 88 + 88, 88, 88, 88);
        [c addTarget:self action:@selector(play1x) forControlEvents:UIControlEventTouchUpInside];
        [c setTitle:@"1x" forState:UIControlStateNormal];
        c.tintColor = UIColor.cyanColor;
        [self.view addSubview:c];
    }
    
    {
        UIButton* c = [UIButton buttonWithType:UIButtonTypeSystem];
        c.frame = CGRectMake(88 + 88 + 88 + 88, 88, 88, 88);
        [c addTarget:self action:@selector(play2x) forControlEvents:UIControlEventTouchUpInside];
        [c setTitle:@"1.75x" forState:UIControlStateNormal];
        c.tintColor = UIColor.cyanColor;
        [self.view addSubview:c];
    }
    
    
    
    player->time_callback() = [d](auto current,auto duration){
        dispatch_async(dispatch_get_main_queue(), ^{
            d.value = current / duration;
        });
    };
}
- (void)pause{
    player->pause();
}

- (void)play{
    player->play();
}
- (void)playp5{
    player->rate(0.75);
}
- (void)play1x{
    player->rate(1);
}
- (void)play2x{
    player->rate(1.75);
}
- (void)slider:(UISlider *)slider{
    player->seek_to(slider.value);
}
- (void)sliderEnd:(UISlider *)slider{
    player->play();
}
- (void)call:(NSNumber *)n{
    video.setScreen(self.render.width, self.render.height);
    auto frame = player->get_current_frame();
    video.render(frame);
}
- (void)viewWillAppear:(BOOL)animated{
    self.render.layer.frame = self.view.bounds;
    [super viewWillAppear:animated];
}
- (void)dealloc
{
    delete player;
    [self.render stop];
}
@end



@implementation tempController

- (void)viewDidLoad{
    [super viewDidLoad];
    {
        UIButton * b = [UIButton buttonWithType:UIButtonTypeSystem];
        [b setTitle:@"相册" forState:UIControlStateNormal];
        b.backgroundColor = UIColor.blueColor;
        [self.view addSubview:b];
        b.frame = CGRectMake(0, 0, 200, 200);
        [b addTarget:self action:@selector(goGallery) forControlEvents:UIControlEventTouchUpInside];
    }
    
    {
        UIButton * b = [UIButton buttonWithType:UIButtonTypeSystem];
        [b setTitle:@"文件" forState:UIControlStateNormal];
        b.backgroundColor = UIColor.blueColor;
        [self.view addSubview:b];
        b.frame = CGRectMake(200, 0, 200, 200);
        [b addTarget:self action:@selector(goExploer) forControlEvents:UIControlEventTouchUpInside];
      
    }
}

- (void)goGallery{
    UIImagePickerController* pick = [[UIImagePickerController alloc] init];
    pick.delegate = self;
    pick.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    pick.mediaTypes = @[(id)kUTTypeMovie];
    pick.allowsEditing = false;
    [self showViewController:pick sender:nil];
}
- (void)goExploer{
    UIDocumentPickerViewController* pick = [[UIDocumentPickerViewController alloc]
                                            initWithDocumentTypes:@[@"public.movie"] inMode:UIDocumentPickerModeImport];
    

    pick.allowsMultipleSelection = false;
    pick.delegate = self;
    [self presentViewController:pick animated:true completion:nil];
}
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey,id> *)info{
    iewController * vc = [[iewController alloc] init];
    vc.u = info[UIImagePickerControllerMediaURL];
    [picker dismissViewControllerAnimated:true completion:^{
        [self showViewController:vc sender:nil];
    }];
//    NSURL
}
- (void)documentPicker:(UIDocumentPickerViewController *)controller didPickDocumentsAtURLs:(NSArray<NSURL *> *)urls{
    iewController * vc = [[iewController alloc] init];
    vc.u = urls.firstObject;
    [controller dismissViewControllerAnimated:true completion:^{
        [self showViewController:vc sender:nil];
    }];
}
- (void)documentPickerWasCancelled:(UIDocumentPickerViewController *)controller{
    NSLog(@"dasdasd");
}

@end
