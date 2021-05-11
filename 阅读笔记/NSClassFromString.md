##[NSClassFromString](https://juejin.cn/post/6844903686175457288)
####最后再整理一下条件的逻辑以及代码风格，得到 NSClassFromString 的实现如下：

```
Class _Nullable NSClassFromString(NSString *aClassName) {
    if (!aClassName) { return Nil; }
    
    NSUInteger classNameLength = [aClassName length];
    char buffer[1000];
    
    // @"Big\0Dog" 以及 @"🐶" 都会使得
    // classNameLength == strlen(buffer) 不成立
    if ([aClassName getCString:buffer maxLength:1000 encoding:NSUTF8StringEncoding]
        && classNameLength == strlen(buffer)) {
        return objc_lookUpClass(buffer);
    } else if (classNameLength == 0) {
        // 检查是否空字符串 @""，这个分支要处理的情况不太理解
        return objc_lookUpClass([aClassName UTF8String]);
    }
    
    for (int i = 0; i < classNameLength; i++) {
        // 如果 aClassName 中含有 \0 字符，向外返回 Nil
        // 比如 @"Big\0Dog" 的情况
        if ([aClassName characterAtIndex:i] == 0) {
            return Nil;
        }
    }
    
    return objc_lookUpClass([aClassName UTF8String]);
}

```

* 对代码的一些理解也写在了上面。主要逻辑就是从 NSString 获取到 C 风格的字符串(以 \0 结尾)，然后使用 objc_lookUpClass 查找对应的类实现。对不合法的字符串(非终止位置带有 \0)。以及由于 OC 中允许以非 Ascii 字符的方式定义类(如 Emoji)，所以也需要对这种情况进行处理，得到相应的 C 字符串。

