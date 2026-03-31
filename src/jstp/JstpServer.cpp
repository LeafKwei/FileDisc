#include <QDate>
#include "def/config.hpp"
#include "jstp/JstpServer.hpp"
FILEDISC_BEGIN

JstpServer::JstpServer()
    : threads_(MAX_THRAED)
    , port_(SERVER_PORT)
{
    
}

auto JstpServer::listen() -> ErrBox{
    /* 初始化信号连接 */
    initQConnections();
    
    /* 开启对TCP请求的监听 */
    if(!tcpserver_.listen(QHostAddress::Any, port_)){
        return ErrBox(ErrCode::TCPListen, "Failed to listen: "+ tcpserver_.errorString());
    }
    
    /* 开启对广播请求的监听 */
    auto err = initBroadcast();
    if(err){
        return err;
    }
    
    return OkBox();
}

auto JstpServer::setPort(quint16 port) -> void{
    port_ = port;
}

auto JstpServer::setSharedDirectory(const QString &path) -> void{
    auto backup = sharedDir_.path();
    sharedDir_.setPath(path);
    if(!sharedDir_.exists()){
        sharedDir_.setPath(backup);
    }   
}

auto JstpServer::addHook(RequestHook hook) -> void{
    hooks_.push_back(hook);
}

auto JstpServer::initBroadcast() -> ErrBox{
    auto ok = broadcast_.bind(
        port_,
        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint
    );
    
    if(!ok){
        return ErrBox(ErrCode::UDPBind, "Failed to bind: " + broadcast_.errorString());
    }
    
    return OkBox();
}

auto JstpServer::initQConnections() -> void{
    connect(&tcpserver_, SIGNAL(newConnection()), this, SLOT(at_requestComing()));
    connect(&broadcast_, SIGNAL(readyRead()), this, SLOT(at_broadcastComing()));
}

void JstpServer::at_requestComing(){
    qDebug() << "Get TCP Request...";
}

void JstpServer::at_broadcastComing(){
    qDebug() << "Get Broadcast Request...";
}


FILEDISC_END