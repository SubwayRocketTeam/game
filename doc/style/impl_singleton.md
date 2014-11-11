싱글톤 구현 스타일
====

* lazy-eval 사용 X
  * AppDelegate에서 초기화

#### Header
```C++
class Object{
public:
  static Object *create();
  static Object *getInstance();
};
```

### Source
```C++
#include "object.h"

static Object *instance = nullptr;

Object *Object::create(){
  instance = new Object();
  
  if(instance && instance->init()){
    instance->autorelease();
    return instance;
  }
  CC_SAFE_DELETE(instance);
  return nullptr;
}
Object *Object::getInstance(){
  return instance;
}
```
