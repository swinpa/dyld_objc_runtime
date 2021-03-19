##category中添加属性的问题
* 分类中可以添加属性，但编译器不会为分类中的属性自动生成setter，getter 方法，也没有对应的成员变量生成
* 我们可以手动的给分类的属性添加setter，getter 方法，并在方法中通过运行时为其关联变量
- 关联方法如下
	* objc_setAssociatedObject(id _Nonnull object, const void * _Nonnull key,
                         id _Nullable value, objc_AssociationPolicy policy),底层调用了runtime的_object_set_associative_reference 方法，该方法在objc_references.mm中定义
	* objc_getAssociatedObject(id _Nonnull object, const void * _Nonnull key)
* 关联的大致原理如下
	* runtime中有一个名叫AssociationsManager 关联管理类，里面有一个static（静态）hashMap（static AssociationsHashMap *_map;）该哈希表存放着所有关联过属性的对象关联表，数据结构大致如下
	
	```
	AssociationsHashMap = [
		ObjectAssociationMap1 = [ //根据对象地址找到对应的ObjectAssociationMap
			ObjcAssociation,//在ObjectAssociationMap 中根据key找到对应的ObjcAssociation
			ObjcAssociation
		],
		ObjectAssociationMap2 = [
			ObjcAssociation,
			ObjcAssociation
		],
		ObjectAssociationMap3 = [
			ObjcAssociation,
			ObjcAssociation
		],
	]
	```
	```
	class ObjcAssociation {
		uintptr_t _policy;
		id _value;
    public:
    	ObjcAssociation(uintptr_t policy, id value) : _policy(policy), _value(value) {}
     	ObjcAssociation() : _policy(0), _value(nil) {}
     	uintptr_t policy() const { return _policy; }	
     	id value() const { return _value; }	
     	bool hasValue() { return _value != nil; }
   
    };

	```
	
* 关联时，根据当前对象地址，从AssociationsHashMap中找到对象对应的ObjectAssociationMap，然后再根据key，在
ObjectAssociationMap 中找到关联信息

### 如何把framework的私有方法公开？
* 在分类中定义一个方法跟私有方法同名的就可以了
### 如何把framework的私有属性（在扩展里面定义的属性）公开？
* 在分类中定义一个与私有属性同名的属性就可以了


