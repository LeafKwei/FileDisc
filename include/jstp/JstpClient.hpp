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
    auto requestHost() -> Result<qint32>;   //向子网的所有server发送广播，请求其主机信息
    auto requestFile(        //向指定的服务端发起文件下载请求，返回请求编号(后续通过信号通知请求结果时会使用该id)
        const JstpHostField &host, 
        const QString &beginPath, 
        const QString &targetName) -> Result<qint32>;
    auto requestDir(         //向指定的服务端发起目录下查询请求，返回请求编号(后续通过信号通知请求结果时会使用该id)
        const JstpHostField &host, 
        const QString &beginPath, 
        const QString &targetName) -> Result<qint32>;
    auto setDownloadDirectory(const QString &path) -> void; //设置下载目录所在路径，如果目录不存在，则默认使用程序安装目录
    
private:
    auto initBroadcast() -> ErrBox;
    auto initHostsock() -> ErrBox;
    auto initQConnections() -> void;
    auto nextJobId() -> qint32;
    
private:
    qint16 port_;
    qint32 jobid_;
    QUdpSocket broadsock_;
    QUdpSocket hostsock_;
    ThreadManager threads_;
    
signals:
    void to_requestHostJobDone(qint32 id, ErrCode err);

private slots:
    void at_hostComing();
};

FILEDISC_END
#endif
