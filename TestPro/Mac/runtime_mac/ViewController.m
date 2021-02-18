//
//  ViewController.m
//  runtime_mac
//
//  Created by admin on 2019/1/29.
//  Copyright © 2019 swinpa. All rights reserved.
//

#import "ViewController.h"

@implementation TView

- (void)dealloc {
    NSLog(@"");
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    
//    NSString *className = [NSString stringWithUTF8String:object_getClassName(self)];
//    [self testMethod];
//    NSLog(@"");
    
    NSButton *btn = [NSButton buttonWithTitle:@"click me" target:self action:@selector(buttonClick)];
    CGFloat w = [NSScreen mainScreen].frame.size.width;
    CGFloat h = [NSScreen mainScreen].frame.size.height;
    
    btn.frame = NSMakeRect(30, 40, 450, 50);
    [self.view addSubview:btn];
//    btn.backgroundColor = [NSColor yellowColor];
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void)testMethod {
    NSLog(@"%s",__func__);
}

- (void)buttonClick {
    NSLog(@"%@",self);
    NSLog(@"");
    {
        TView *vc = [[TView alloc] init];
        vc.v = [[NSView alloc] init];
        self.wproperty = vc;
        NSLog(@"");
    }
    
    
    NSLog(@"");
}

@end
