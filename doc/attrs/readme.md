Attribute
====

* 공격력, 이동속도, HP양 등 Unit이 가지는 속성

프로퍼티
----
* value : 속성의 현재 값
* max : 속성의 최대 값
* bonusValue : 속성 값에 더해질 수치
* bonusRate : 속성 값에 곱해질 배율

값의 계산
----
```
= (value + bonusValue) * (1.0f + bonusRate)
```

종류
----
* speed : 이동 속도
* hp : 체력
* mp : 마력
* hpRegen : 초당 hp 회복량
* mpRegen : 초당 mp 회복량
* attack : 공격력
* defence : 방어력
* attackSpeed : 공격 속도 비율(%)
* criticalRate
* accuracyRate
* evasionRate 
