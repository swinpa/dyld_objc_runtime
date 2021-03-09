//
//  ViewController.m
//  runtime_test_proj_iOS
//
//  Created by admin on 2019/1/29.
//  Copyright © 2019 swinpa. All rights reserved.
//

#import "ViewController.h"
#import <objc/runtime.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor yellowColor];
    
    @autoreleasepool {
        NSObject *obj0 = [[[NSObject alloc] init] autorelease];
        @autoreleasepool {
            NSObject *obj10 = [[[NSObject alloc] init] autorelease];
            @autoreleasepool {
                NSObject *obj20 = [[[NSObject alloc] init] autorelease];
            }
        }
        NSObject *obj1 = [[[NSObject alloc] init] autorelease];
    }
    
}


@end
