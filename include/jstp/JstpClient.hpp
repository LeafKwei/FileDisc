#ifndef JSTPCLIENT_H
#define JSTPCLIENT_H

#include "def/types.hpp"
#include "jstp/HostStruct.hpp"
FILEDISC_BEGIN

class JstpClient{
public:
    using HostVector = QVector<HostStruct>;
    
public:
    explicit JstpClient() =default;
    HostVector discover(qint32 timeout) const noexcept; //发送广播，查询局域网内所有可用的JstpServer
    void connect(const HostStruct &host);      //连接指定的主机，如果连接失败则抛出异常
    void disconnect();                         //断开连接，如果出错则抛出异常
    
private:
    
    
signals:
    void on_connected();
    
};

FILEDISC_END
#endif
