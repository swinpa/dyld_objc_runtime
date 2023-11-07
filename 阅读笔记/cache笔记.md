
typedef uintptr_t SEL;

```
struct objc_class : objc_object {
    cache_t cache; // formerly cache pointer and vtable
}
```
在类中有一cache_t cache成员专门用来缓存消息的

```
struct cache_t {
    struct bucket_t *_buckets;
    mask_t _mask;//mask 的值对于 bucket 来说，主要是用来在缓存查找时的哈希算法。
    mask_t _occupied;//占用占领 ,capacity 可以获取到 cache_t 中 bucket 的数量
}
```

```
struct bucket_t {
    MethodCacheIMP _imp;
    /*
    typedef uintptr_t cache_key_t;//这个其实就是sel
    */
    cache_key_t _key;
}
```

cache_t中通过_buckets指向的内存缓存消息，在进行缓存时是通过已sel作为key进行hash
计算从而得到sel对应的bucket在_buckets内存中的下标

	其中的解决hash冲突使用的是：开放定址法
	
	开放定值法：从发生冲突的那个单元起，按照一定的次序，从哈希表中找到一个空闲的
	单元。然后把发生冲突的元素存入到该单元的一种方法

	又细分为线性探查法:
		它从发生冲突的单元起，依次判断下一个单元是否为空，当达到最后一个单元时，
		再从表首依次判断。直到碰到空闲的单元或者探查完全部单元为止。
		
cache_t 缓存扩容发生在cache_fill的前期，首先会判断cache是否为空，为空则申请空间，不为空时会判断是否已满，满了则进行扩容

当有足够的空间后调用find方法在缓存中查找合适的位置来存放需要缓存的bucket，通过对比hash计算得到的index所对应的bucket中的key，是否跟当前要查找的key一致，一致则说明找到缓存位置

缓存大小：INIT_CACHE_SIZE == 4