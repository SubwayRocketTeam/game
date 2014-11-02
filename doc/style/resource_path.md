리소스 경로 설정
====

```C++
Sprite::create("player.png"); /* X */
Sprite::create(R::Player); /* O */
```

#### common/resource.h
```C++
namespace R{
  _RESL(Player);
};
```
#### common/resource.cpp
```C++
namespace R{
  _RESD(Player, "player.png");
};
```
