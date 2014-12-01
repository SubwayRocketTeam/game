TestUnit
====

```Ruby
class LoginTest < GeniusTestUnit
  def query
    pkt = LoginRequest.new
    pkt.id = "pjc0247"
    pkt.pw = "asdf1234"
    return pkt
  end
  
  def should
    resp = LoginResponse.new
    resp.result = true
    resp.nickname = "asdf"
    return resp
  end
end
```
