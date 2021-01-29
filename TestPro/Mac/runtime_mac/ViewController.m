//
//  ViewController.m
//  runtime_mac
//
//  Created by admin on 2019/1/29.
//  Copyright © 2019 swinpa. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    
    NSString *className = [NSString stringWithUTF8String:object_getClassName(self)];
    [self testMethod];
    NSLog(@"");
    
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void)testMethod {
    NSLog(@"%s",__func__);
}

@end
