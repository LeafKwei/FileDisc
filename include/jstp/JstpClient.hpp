#ifndef JSTPCLIENT_HPP
#define JSTPCLIENT_HPP

#include <QObject>
#include <QUdpSocket>
#include "def/err.hpp"
#include "def/types.hpp"
#include "jstp/JstpPayload.hpp"
#include "thread/ThreadManager.hpp"
FILEDISC_BEGIN

/*///////// 实现了JSTP协议的客户端 /////////*/
class JstpClient : public QObject{
    Q_OBJECT
public:
    explicit JstpClient();
    auto initClient() -> ErrBox;
    auto requestHost() -> Result<quint32>;   //向子网的所有server发送广播，请求其主机信息
    auto requestFile(        //向指定的服务端发起文件下载请求，返回请求编号(后续通过信号通知请求结果时会使用该id)
        const JstpHostField &host, 
        const QString &beginPath, 
        const QString &targetName) -> Result<quint32>;
    auto requestDir(         //向指定的服务端发起目录下查询请求，返回请求编号(后续通过信号通知请求结果时会使用该id)
        const JstpHostField &host, 
        const QString &beginPath, 
        const QString &targetName) -> Result<quint32>;
    
private:
    auto initBroadcast() -> ErrBox;
    auto initHostsock() -> ErrBox;
    auto initQConnections() -> void;
    

private:
    qint16 port_;
    QUdpSocket broadsock_;
    QUdpSocket hostsock_;
    ThreadManager threads_;
    
signals:


private slots:
    void at_hostComing();
};

FILEDISC_END
#endif
