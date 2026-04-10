#ifndef JFTPCLIENT_HPP
#define JFTPCLIENT_HPP

#include "def/err.hpp"
#include "def/types.hpp"
#include "jftp/req/JftpRequest.hpp"
#include "jftp/rsp/JftpResponse.hpp"
FILEDISC_BEGIN

class JftpClient{
public:
    explicit JftpClient();
    auto initClient() -> ErrBox; //初始化客户端
    auto sendRequestSync(JftpRequest *req) -> Result<JftpResponse*>; //采用同步IO发送请求，并在请求完成后返回响应对象
    auto sendRequestAsyn(JftpRequest *req) -> Result<idtype>; //采用异步IO发送请求，并在请求完成后通过信号传递响应对象
    
signals:
    void to_requestFinished(JftpResponse *rsp, ErrCode err);
    
private slots:
    void at_requestDone(JftpResponse *rsp, ErrCode err);
};

FILEDISC_END
#endif
