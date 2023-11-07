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
#import <CoreImage/CoreImage.h>

#include <pthread.h>

#import <StoreKit/StoreKit.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor yellowColor];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
    });
         
    [self.view setNeedsLayout];
    [self.view layoutIfNeeded];
    [self.view setNeedsDisplay];
    NSTimer *t = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(viewDidLoad) userInfo:nil repeats:true];
    [self.view performSelector:@"" onThread:[NSThread mainThread] withObject:nil waitUntilDone:true];
    NSThread *th = [[NSThread alloc] initWithBlock:^{
        
    }];
    [self performSelector:@selector(doSomething)];
    [self performSelectorInBackground:@selector(doSomething) withObject:nil];
    CFRunLoopRef rl;
    CFRunLoopWakeUp(rl);
    [self.view setNeedsLayout];
    [self.view layoutIfNeeded];
    
    [self.view.layer setTimeOffset:0];
    
    NSOperation *s;
    
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

//MLeadFinder 实现方案
+ (void)swizzleSEL:(SEL)originalSEL withSEL:(SEL)swizzledSEL {
    
    Class class = [self class];
    
    //class_getInstanceMethod有可能是从父类methods获取到的
    Method originalMethod = class_getInstanceMethod(class, originalSEL);
    Method swizzledMethod = class_getInstanceMethod(class, swizzledSEL);
    
    BOOL didAddMethod =
    class_addMethod(class,
                    originalSEL,
                    method_getImplementation(swizzledMethod),
                    method_getTypeEncoding(swizzledMethod));
    
    if (didAddMethod) {
        /*
         添加成功，说明类方法列表中《没有》originalSEL方法，
         通过Method originalMethod = class_getInstanceMethod(class, originalSEL);获取到的originalMethod其实父类的
         
         添加成功后本类的originalSEL已经绑定了swizzledMethod.imp
         但swizzledSEL还没跟原类的originalMethod.imp绑定到一起
         故还需要调用class_replaceMethod将swizzledSEL跟originalMethod.imp进行绑定
         */
        class_replaceMethod(class,
                            swizzledSEL,
                            method_getImplementation(originalMethod),
                            method_getTypeEncoding(originalMethod));
    } else {
        /*
         添加不成功，说明原来类方法列表中《有》originalSEL方法，也就是
         class_getInstanceMethod(class, originalSEL);获取到的method是类的methods列表中的，而非父类的methods中的
         
         注意注意！！！！！
         如果没经过class_addMethod这一步，直接调用method_exchangeImplementations方法进行替换
         那么就会出现父类的method被交换的情况，然而我们原本要替换的是本类的，所以就出bug了，影响了父类的行为
         
         */
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}

- (void)doSomething {
    NSLog(@"do some thing");
}

@end
