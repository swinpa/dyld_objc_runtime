//
//  ViewController.m
//  runtime_test_proj_iOS
//
//  Created by admin on 2019/1/29.
//  Copyright © 2019 swinpa. All rights reserved.
//

#import "ViewController.h"
#import <objc/runtime.h>
#include <mach-o/dyld.h>
#import <CoreImage/CoreImage.h>>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor yellowColor];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
    });
    
}

+ (void)swizzSysMethod:(NSString *)systemSelector swizzSel:(NSString *)swizzSelector andClass:(Class)class {
    //获得viewController的生命周期方法的selector
    SEL systemSel = NSSelectorFromString(systemSelector);;
    //自己实现的将要被交换的方法的selector
    SEL swizzSel = NSSelectorFromString(swizzSelector);
    
    //两个方法的Method
    Method systemMethod = class_getInstanceMethod(class, systemSel);
    Method swizzMethod = class_getInstanceMethod(class, swizzSel);
    
    //首先动态添加方法，实现是被交换的方法，返回值表示添加成功还是失败
    BOOL isAdd = class_addMethod(class, systemSel, method_getImplementation(swizzMethod), method_getTypeEncoding(swizzMethod));
    if (isAdd) {
        //如果成功，说明类中不存在这个方法的实现
        //将被交换方法的实现替换到这个并不存在的实现
        class_replaceMethod(class, swizzSel, method_getImplementation(systemMethod), method_getTypeEncoding(systemMethod));
    }else{
        //否则，交换两个方法的实现
        method_exchangeImplementations(systemMethod, swizzMethod);
    }
}

@end
