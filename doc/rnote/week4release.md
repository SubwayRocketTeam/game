선독
----
* 이 게임은 적 로봇을 파괴하여 드랍된 쓰레기를 모은 뒤
* 모은 쓰레기로 다시 적에게 더 강력한 로봇을 보내 더 오래 살아남는 쪽이 승리하는 서바이벌 게임입니다.
* 하지만, 아직 네트워크 대전 기능의 미완으로 적에게 로봇을 보내도 아무 의미가 없으므로
* 적 스폰 키를 눌러도 적 스테이지가 아닌, 아군 스테이지에서 나오도록 처리하였습니다.
<br><br>
* 현재 버전에서의 로봇은 두가지 종류가 있습니다
* z키를 누르면 스폰되는 로봇
* 자연적으로 스폰되는 로봇

조작 방법
----
* __이동__ : 방향키
* __공격__ : 왼쪽 마우스 클릭
* __대쉬__ : 오른쪽 마우스 클릭
* __숫자 1__ : 아드레날린 스킬
* __쉬프트__ : 업그레이드 창 보기
* __탭__ : 상대 진영 보기
* __z__ : 최하급 로봇 스폰
* __ESC__ : 일시 정지

변경 사항
----
* __UI__
  * 미니맵 위치가 우측 상단으로 이동
  * Tab키 누르면 상대방 진영이 보임
    * 현재는 상대방 진영에 아무것도 없어서 빈 스테이지만 보임
  * Shift키 누르면 상단에서 업그레이드 바 내려옴
    * 업그레이드 코스트도 표시됨
  * 플레이어 체력 게이지의 변경
  * 하단에 쓰레기 탱크 UI 추가
  * 로그인 씬 추가
* __스킬__
  * 패시브 스킬이 지속 기간을 가지도록 변경
    * 아드레날린 스킬의 지속시간 -> 5초
  * 아드레날린 스킬 지속 기간 동안 플레이어가 빨간색으로 블링크
* __게임플레이__
  * 올라가 있을 경우 지속적으로 체력이 회복되는 RepairZone의 추가
    * 맵 상의 이상한 빨간 구역
  * 게임이 재미 없을 경우 minsoo-valley 하러 갈 수 있는 기능 추가
* __플레이어__
  * 총 쏠 때 총알의 페이드 효과 추가
  * 주변의 쓰레기를 빨아들임
  * 맞으면 블링크, 넉백의 처리
* __적 로봇__
  * 적을 잡으면 잡은 위치에서 쓰레기가 드랍
  * 원형 탄막을 쏘는 로봇 추가
  * z키를 누르면 랜덤 위치에 적 로봇 생성
    * 아무것도 안쏘고, 부딪히면 데미지만 주는 최하급 로봇
* __물리__
  * 기존 물리 엔진 떼고 자체 충돌 처리 코드 주가.

보이지 않는 변경 사항
----
* [빌드 속도 향상](https://github.com/SubwayRocketTeam/cocos2d-x-custom/commit/08ba83082b85bae6650d536fa9574516151a4cb1)
