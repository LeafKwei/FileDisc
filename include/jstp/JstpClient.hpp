#ifndef JSTPCLIENT_HPP
#define JSTPCLIENT_HPP

#include <QDir>
#include <QObject>
#include <QUdpSocket>
#include "def/err.hpp"
#include "def/types.hpp"
#include "jstp/JstpPayload.hpp"
#include "thread/ThreadManager.hpp"
FILEDISC_BEGIN
class JstpJob;

/*///////// 实现了JSTP协议的客户端 /////////*/
class JstpClient : public QObject{
    Q_OBJECT
public:
    explicit JstpClient(const QString &name="Client-NoName");
    auto initClient() -> ErrBox;
    auto requestHost() -> Result<qint32>;   //向子网的所有server发送广播，请求其主机信息
    auto requestFile(        //向指定的服务端发起文件下载请求，返回请求编号(后续通过信号通知请求结果时会使用该id)
        const JstpHostField &server, 
        const QString &beginPath, 
        const QString &targetName) -> Result<qint32>;
    auto requestDir(         //向指定的服务端发起目录下查询请求，返回请求编号(后续通过信号通知请求结果时会使用该id)
        const JstpHostField &server, 
        const QString &beginPath, 
        const QString &targetName) -> Result<qint32>;
    auto setDownloadDirectory(const QString &path) -> void; //设置下载目录所在路径，如果目录不存在，则默认使用程序安装目录
    
private:
    auto initLoalHost() -> ErrBox;
    auto initUdpReceiver() -> ErrBox;
    auto initQConnections() -> void;
    auto nextJobId() -> qint32;
    auto isBadJob(JstpJob *job) -> bool;
    auto submit(JstpJob *job) -> Result<qint32>;
    auto fillHostReq(JstpPayload &req) -> ErrBox;
    auto fillFileReq(JstpPayload &req) -> ErrBox;
    
private:
    qint16 port_;
    qint32 jobid_;
    QDir downloadDir_;
    QString name_;
    JstpHostField local_;
    QUdpSocket udprecvr_;
    ThreadManager manager_;
    
signals:
    void to_requestHostJobDone(qint32 id, ErrCode err);

private slots:
    void at_hostComing();
};

FILEDISC_END
#endif
