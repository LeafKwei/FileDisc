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
    auto discover(qint32 timeout) const -> HostVector; //发送广播，查询局域网内所有可用的JstpServer
    auto connect(const HostStruct &host) -> ErrStruct; //连接指定的主机
    auto disconnect() -> ErrStruct;                    //断开连接
    
private:
    
    
signals:
    void on_connected();
    
};

FILEDISC_END
#endif
