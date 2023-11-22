//
//  AppDelegate.m
//  CCRender
//
//  Created by wenyang on 2023/11/13.
//

#import "AppDelegate.h"

#import "iewController.h"
@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    _window = [UIWindow new];
    UIViewController* c = [tempController new];
    UINavigationController * a = [[UINavigationController alloc] initWithRootViewController:c];
    _window.rootViewController = a;
    [_window makeKeyAndVisible];
   
    
    return YES;
}

@end
