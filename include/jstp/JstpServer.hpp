#ifndef JSTPSERVER_H
#define JSTPSERVER_H

#include <QObject>
#include "def/types.hpp"
#include "jstp/RequestHook.hpp"
#include "jstp/JstpRequest.hpp"
FILEDISC_BEGIN

/* Server需要同时监听两个端口：广播端口、外部client访问端口 */
class JstpServer{
public:
    explicit JstpServer() =default;
    void listen() noexcept; //开启监听
    void setPort(quint16 port) noexcept; //设置监听的外部client端口
    void addHook(RequestHook hook) noexcept; //添加请求钩子，可自由修改请求内容，同时也可过滤请求(通过返回false)

private:

};

FILEDISC_END
#endif
