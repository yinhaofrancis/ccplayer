//
//  iewController.m
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#import "iewController.h"
#import <objc/runtime.h>
#import <objc/message.h>
#import <MobileCoreServices/MobileCoreServices.h>
#include <ccmedia/encoder/encoder.hpp>
#include <ccmedia/encoder/writer.hpp>
@interface iewController ()
@property (weak, nonatomic) IBOutlet UISlider *sliderview;
@property (weak, nonatomic) IBOutlet UIButton *olayButton;

@property (weak, nonatomic) IBOutlet UIView *widgetview;



@property (weak,nonatomic) NSTimer * timer;

@end

@implementation iewController

- (void)viewDidLoad {
    [super viewDidLoad];
    id  sharedObject = [objc_lookUpClass("AVAudioSession") performSelector:sel_getUid("sharedInstance")];
        [sharedObject performSelector:sel_getUid("setActive:error:") withObject:@true withObject:nil];


//    auto a = "/Users/haoyin/Desktop/gamesci_2022PV03.mp4";
    
    
//    _player->play();
    __weak iewController *ws = self;
    self.render = [[CCPlayer alloc] initWithUrl:_u];
    [self.view.layer addSublayer:self.render.layer];
//    self.render.layer.backgroundColor = UIColor.redColor;
    self.render.observerTime = ^(double f) {
        ws.sliderview.value = f;
        ws.olayButton.selected = ws.render.state == player_state_playing;
        if(!CGRectEqualToRect(ws.render.layer.frame, ws.view.bounds)){
            ws.render.layer.frame = ws.view.bounds;
        }
    };
    self.render.layer.zPosition = -1;
    
    [self showWidget];
}

- (IBAction)play:(UIButton *)b{
    if(b.selected){
        [self.render pause];
    }else{
        [self.render play];
    }
    b.selected = !b.selected;
    [self showWidget];
}
- (IBAction)playp5{
    [self.render rate:0.5];
}
- (IBAction)play1x{
    [self.render rate:1];
}
- (IBAction)play2x{
    [self.render rate:2.0];
//    player->rate(2.0);
}
- (IBAction)slider:(UISlider *)slider{
    [self.render seek:slider.value];
}
- (IBAction)sliderEnd:(UISlider *)slider{
    [self.render play];
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillDisappear:animated];
    self.render.layer.frame = self.view.bounds;
}
- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [super touchesEnded:touches withEvent:event];
    [self showWidget];
}
-(void)showWidget{
    if(self.timer != nil){
        [self.timer invalidate];
        self.timer = nil;
    }
    self.timer = [NSTimer scheduledTimerWithTimeInterval:3 repeats:false block:^(NSTimer * _Nonnull timer) {
        [UIView animateWithDuration:0.24 delay:0 options:UIViewAnimationCurveEaseInOut animations:^{
            self.widgetview.alpha = 0;
        } completion:^(BOOL finished) {
            
        }];
        [timer invalidate];
    }];
    [UIView animateWithDuration:0.24 delay:0 options:UIViewAnimationCurveEaseInOut animations:^{
        self.widgetview.alpha = 1;
    } completion:^(BOOL finished) {
        
    }];
}
- (void)dealloc{
    [self.render stop];
}

@end


@interface tempController ()<UITextFieldDelegate>

@end

@implementation tempController

- (void)viewDidLoad{
    [super viewDidLoad];
    
}
- (BOOL)textFieldShouldReturn:(UITextField *)textField{
    NSURL * url = [[NSURL alloc] initWithString:self.pathView.text];
    if(url != nil){
        [self performSegueWithIdentifier:@"play" sender:url];
        return true;
    }
    return false;
}
- (void)goGallery{
//    UIImagePickerController* pick = [[UIImagePickerController alloc] init];
//    pick.delegate = self;
//    pick.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
//    pick.mediaTypes = @[(id)kUTTypeMovie];
//    pick.allowsEditing = false;
//    [self showViewController:pick sender:nil];
    
    
}
- (IBAction)goExploer{
    UIDocumentPickerViewController* pick = [[UIDocumentPickerViewController alloc]
                                            initWithDocumentTypes:@[@"public.movie"] inMode:UIDocumentPickerModeImport];
    

    pick.allowsMultipleSelection = false;
    pick.delegate = self;
    [self presentViewController:pick animated:true completion:nil];
}
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey,id> *)info{

    [picker dismissViewControllerAnimated:true completion:^{
        [self performSegueWithIdentifier:@"play" sender:info[UIImagePickerControllerMediaURL]];
    }];
//    NSURL
}
- (void)documentPicker:(UIDocumentPickerViewController *)controller didPickDocumentsAtURLs:(NSArray<NSURL *> *)urls{
    [controller dismissViewControllerAnimated:true completion:^{
        [self performSegueWithIdentifier:@"play" sender:urls.firstObject];
    }];
}


- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    iewController* dest = segue.destinationViewController;
    dest.u = sender;
}

@end
