#ifndef JSTPCLIENT_HPP
#define JSTPCLIENT_HPP

#include <QObject>
#include <QUdpSocket>
#include "def/err.hpp"
#include "def/types.hpp"
#include "jstp/JstpPayload.hpp"
FILEDISC_BEGIN

/*///////// 实现了JSTP协议的客户端 /////////*/
class JstpClient : public QObject{
    Q_OBJECT
    using ArgHolder = int;
public:
    explicit JstpClient();
    auto listen() -> ErrBox;  //UDP异步监听服务端相应的主机信息，监听结果通过信号反馈
    auto broadcastToLAN() -> ErrBox;   //向子网的所有server发送广播，以便server向client发送主机信息
    auto request(ArgHolder) -> Result<quint32>; //向服务端发出JSTP请求，需要提供：主机信息+请求内容，返回请求编号(后续通过信号通知请求结果时会使用该id)
    auto setPort(qint16 port) -> void; //设置UDP监听的端口
    
private:
    auto sendHostRequest(ArgHolder) -> ErrBox;
    auto makeHostRequest() -> ArgHolder;
    auto initBroadcast(QUdpSocket &broadcast) -> ErrBox;
    auto initHostsock() -> ErrBox;
    auto initQConnections() -> void;
    

private:
    qint16 port_;
    QUdpSocket hostsock_;
    
signals:


private slots:
    void at_hostComing();
};

FILEDISC_END
#endif
