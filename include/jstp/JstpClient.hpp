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
    HostVector discover(qint32 timeout) const; //发送广播，查询局域网内所有可用的JstpServer
    ErrStruct connect(const HostStruct &host); //连接指定的主机
    ErrStruct disconnect();                    //断开连接
    
private:
    
    
signals:
    void on_connected();
    
};

FILEDISC_END
#endif
