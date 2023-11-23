//
//  iewController.h
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#import <UIKit/UIKit.h>
#import "CCPlayer.h"
NS_ASSUME_NONNULL_BEGIN



@interface iewController : UIViewController
@property(nonatomic,strong) CCPlayer* render;

@property(nonatomic,strong) NSURL * u;
@end

@interface tempController : UIViewController<UIImagePickerControllerDelegate,UINavigationControllerDelegate,UIDocumentPickerDelegate>
@property (weak, nonatomic) IBOutlet UITextField *pathView;

@end



NS_ASSUME_NONNULL_END


