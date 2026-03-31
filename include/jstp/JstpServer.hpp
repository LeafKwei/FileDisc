#ifndef JSTPSERVER_HPP
#define JSTPSERVER_HPP

#include <QDir>
#include <QObject>
#include <QVector>
#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include "def/err.hpp"
#include "def/types.hpp"
#include "jstp/RequestHook.hpp"
#include "jstp/JstpPayload.hpp"
#include "thread/ThreadManager.hpp"
#include "utility/LocalLogger.hpp"
FILEDISC_BEGIN

/*///////// 实现了JSTP协议的服务端 /////////*/
class JstpServer : public QObject{
    Q_OBJECT
public:
    explicit JstpServer();
    auto listen() -> ErrBox; //异步监听来自客户端的请求(TCP)和广播(UDP)
    auto setPort(quint16 port) -> void; //设置监听的外部client端口
    auto setSharedDirectory(const QString &path) -> void; //设置共享目录所在路径，如果该目录不存在，则维持旧路径
    auto addHook(RequestHook hook) -> void; //添加请求钩子，可自由修改请求内容，同时也可过滤请求(通过返回false)

private:
    auto initBroadcast() -> ErrBox;
    auto initQConnections() -> void;
    
private:
    quint16 port_;
    QDir sharedDir_;
    QVector<RequestHook> hooks_;
    ThreadManager threads_;
    QTcpServer tcpserver_;
    QUdpSocket broadcast_;
    
signals:
    
private slots:
    void at_requestComing(); //处理TCP传输的请求
    void at_broadcastComing(); //处理广播传输的请求
};

FILEDISC_END
#endif
