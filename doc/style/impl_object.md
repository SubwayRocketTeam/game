오브젝트 작성에 대해
====

* 모든 오브젝트는 스스로 움직여야 한다.
  * 다른 오브젝트가 update 호출해주지 않음.
  * 다른 오브젝트가 마우스, 키보드 이벤트 전달해주지 않음
    * (필요한 상호 작용이 있을 경우는 허용)
* 입력의 처리는 KeyboardEventListener, MouseEventListener를 사용한다.
