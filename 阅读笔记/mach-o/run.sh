// 生成 main.o，目标版本 14.0
xcrun -sdk iphoneos clang -c main.c -o main.o -target arm64-apple-ios14.0

// 生成 libPrint.dylib 动态库
xcrun -sdk iphoneos clang -fPIC -shared print.c -o libPrint.dylib -target arm64-apple-ios14.0

// 链接生成可执行文件，"-L .", 表示在当前目录中查找。"-l Print"，链接 libPrint.dylib 动态库
xcrun -sdk iphoneos clang main.o -o main -L . -l Print -target arm64-apple-ios14.0

