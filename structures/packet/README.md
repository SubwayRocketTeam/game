PGen 사용법
====

* packet_def.rb에 패킷 스키마 작성
```Ruby
class LoginPacket < Packet
  required #required 명시된 패킷만 빌드됨
  string "id", 32
  string "pw", 32
end
```
* pgen.rb 파일 실행
  * -s : 소스 파일 경로
  * -d : 출력 경로 (리스트)
  * -p : stdout으로 결과 프리뷰 출력
```
ruby pgen.rb -s packet_def.rb -d 출력 경로1,출력 경로2,...
```
* generate된 packet 사용
