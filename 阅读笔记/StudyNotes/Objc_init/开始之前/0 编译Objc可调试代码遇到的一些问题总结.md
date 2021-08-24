#  编译Objc可调试代码遇到的一些问题总结
## 如何开始一份新的objc代码编译通过呢
1. 去GitHub寻找最新别人通过的（利用轮子）
2. 下载objc源码 接着还需要下载关于系统有关的源码。 
dyld  Libc-1439 libclosure-79 libdispatch-1271    libplatform-254  libpthread-454 xnu-7195   
版本可为 最新版本 结合自己的操作系统   编译过程 缺失的头文件 在这些文件中搜索出来 
实在找不到的就是 一些私有 未公布的文件 估计问题不大 直接注释   

## 为什么项目识别到我们的objc项目 并且断点调试
创建一个空的workspace 在同一个workspace下 
目录结构为 

```
▼ XXX.workspace   
  ▼ objc  
  ▼ macDemoBaseObjc 
  ▼ xxxDemo
  同时在把objc中生成的product拉进macDemoBaseObjc项目文件中即可
   Xcode会自动寻找到他的隐含依赖（依据名字寻找 就会在build过程中也会build objc相关的target ）
```
* 理论基础：
*      一个Target和它的product可以和其他Target联系，如果一个target build需要另一个target的“输出”，可以说成第一个target依赖第二个。如果这俩个target在同一个workspace，Xcode会发现他们的依赖关系，从而build the products按照特定的顺序。这样的关系被称为“ implicit dependency.” 你也可以为俩个targets指定明确的target 依赖关系在build setting里面。例如，你可能build一个library和一个链接这个library的application（同一个workspace）。Xcode可以发现这种关系并且自动build这个library first。然而，你如果要去链接library的某个版本而不是one built in the workspace，你可以在build settings里创建一个确定的依赖关系，它将会覆盖implicit dependency。
*      引用：https://blog.csdn.net/houseq/article/details/24260917
