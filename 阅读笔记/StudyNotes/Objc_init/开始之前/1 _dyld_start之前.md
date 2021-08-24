#  _dyld_start 之前
## 内核挖掘 _dyld_start是怎么被调用到的
> _dyld_start的方法地址的确是在 LC_UNIXTHREAD 段中解析出来的。后续通过thread_setentrypoint 直接将用户态的pc设置到这个地址来执行的。

## _dyld_start 是如何一步步执行到的？
```
▼ execve       // 用户点击了app, 用户态会发送一个系统调用 execve 到内核
  ▼ __mac_execve  // 创建线程
    ▼ exec_activate_image // 在 encapsulated_binary 这一步会根据image的类型选择imgact的方法
      ▼ exec_mach_imgact //主要Mach-o检测 检测头部 解析架构 检查imgp 拒绝dylib bundle （由dyld加载）！！把Mach-o映射到内存中
        ▼ load_machfile //会加载Mach-O中的各种load monmand命令 内部会禁止数据段执行，防止溢出漏洞攻击，还会设置地址空间布局随机化（ASLR），还有一些映射的调整
          ▶︎ parse_machfile  //解析主二进制macho  对于命令的加载会进行多次扫描，当扫描三次之后，并且存在dylinker_command命令时，会执行 load_dylinker()，启动动态链接器 (dyld)
          ▼ load_dylinker // 解析完 macho后，根据macho中的 LC_LOAD_DYLINKER 这个LoadCommand来启动这个二进制的加载器，即 /usr/bin/dyld
            ▼ parse_machfile // 解析 dyld 这个mach-o文件，这个过程中会解析出entry_point
        ▼ activate_exec_state
          ▶︎ thread_setentrypoint // 设置entry_point。
          
```
暂且简单 利用此总结的原因 继续从_dyld_start 内部 来学习其他内容   
引用：https://www.jianshu.com/p/8498cec10a41
