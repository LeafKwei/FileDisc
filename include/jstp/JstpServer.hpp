#ifndef JSTPSERVER_H
#define JSTPSERVER_H

#include <QObject>
#include <QVector>
#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include "def/err.hpp"
#include "def/types.hpp"
#include "jstp/RequestHook.hpp"
#include "jstp/JstpRequest.hpp"
#include "thread/ThreadManager.hpp"
FILEDISC_BEGIN

/* 负责监听指定端口收到的JSTP请求 */
class JstpServer : public QObject{
    Q_OBJECT
public:
    explicit JstpServer();
    auto listen() noexcept -> ErrBox; //开启异步监听
    auto setPort(quint16 port) noexcept -> void; //设置监听的外部client端口
    auto addHook(RequestHook hook) noexcept -> void; //添加请求钩子，可自由修改请求内容，同时也可过滤请求(通过返回false)

private:
    auto initBroadcast() -> ErrBox;
    auto initQConnections() -> void;
    
private:
    quint16 port_;
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
