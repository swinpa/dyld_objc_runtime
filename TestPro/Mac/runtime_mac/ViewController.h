//
//  ViewController.h
//  runtime_mac
//
//  Created by admin on 2019/1/29.
//  Copyright © 2019 swinpa. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface TView : NSObject

@property(nonatomic, strong) NSView *v;

@end

@interface ViewController : NSViewController

@property(nonatomic, weak) TView *wproperty;

@end

@interface Person : NSObject


@end


