//
//  iewController.h
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#import <UIKit/UIKit.h>
#import "CCRenderUIkit.h"
NS_ASSUME_NONNULL_BEGIN



@interface iewController : UIViewController
@property(nonatomic,strong) CCEAGLRender* render;
@property(nonatomic,strong) NSURL * u;
@end

@interface tempController : UIViewController<UIImagePickerControllerDelegate,UINavigationControllerDelegate,UIDocumentPickerDelegate>

@end



NS_ASSUME_NONNULL_END


