Player < [Unit](https://github.com/SubwayRocketTeam/game/blob/master/doc/arch/Unit.md)
====

* 유저의 조종을 받아서 움직이는 Unit

TODO
----
* 유저의 조종을 받지 않는 플레이어와 받는 플레이어의 분리 필요

Player가 가지는 프로퍼티
----
* 소유 스킬 : 타입에 따라 소지하는 스킬
* 습득한 스킬 : 소유 스킬 중 습득하여 사용할 수 있는 스킬
* 인벤토리
  * 포션의 갯수
  * 소지 아이템
* 스카프 객체
* PartedBody 객체
* 경직 시간
* 쿨타임 시간


Player가 할 수 있는 액션
----
* 유저 입력에 따라서
  * 이동
  * 공격
  * 스킬 사용
  * 포션 사용
