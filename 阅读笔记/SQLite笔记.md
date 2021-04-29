##SQLite

![官方文档](https://sqlite.org/docs.html)

#####sqlite 本身支持3种不同的线程modes
1. single-thread. 单线程模式，在这种模式下，所有的互斥了mutex都被禁掉了，所以如果在这种模式下使用多线程访问则是不安全的
2. Multi-thread. 多线程模式，在这种模式下，多线程同时访问同一个数据库连接是安全的（官方文档原文是：Multi-thread. In this mode, SQLite can be safely used by multiple threads provided that no single database connection is used simultaneously in two or more threads.）
3. Serialized. 串行模式，在这种模式下，多线程访问数据库是安全的，不管是单个链接还是多个链接（也就是比Multi-thread 还安全）
