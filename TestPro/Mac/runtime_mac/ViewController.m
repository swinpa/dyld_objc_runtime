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
    __weak TView *wvar1 = nil;
    __weak TView *wvar2 = nil;
    __weak TView *wvar3 = nil;
    
    NSString *addr1 = [NSString stringWithFormat:@"wvar1地址=%p",&wvar1];
    NSString *addr2 = [NSString stringWithFormat:@"wvar2地址=%p",&wvar2];
    NSString *addr3 = [NSString stringWithFormat:@"wvar3地址=%p",&wvar3];
    
    NSLog(@"");
    {
        TView *vc = [[TView alloc] init];
        vc.v = [[NSView alloc] init];
        self.wproperty = vc;
        wvar1 = vc;
        wvar2 = vc;
        wvar3 = vc;
        NSLog(@"");
    }
    
    
    NSLog(@"");
}

@end
