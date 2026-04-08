#include <QDataStream>
#include <QNetworkDatagram>
#include "def/config.hpp"
#include "jstp/jstp.hpp"
#include "jstp/JstpServer.hpp"
FILEDISC_BEGIN

JstpServer::JstpServer(const QString &name)
    : threads_(MAX_THRAED, MAX_JOB)
    , port_(SERVER_PORT)
    , name_(name)
{
    
}

auto JstpServer::initServer() -> ErrBox{
    auto err = initTcpSocket();
    if(err){
        return err;
    }
    
    err = initUdpSocket();
    if(err){
        return err;
    }
    
    initQConnections(); //初始化信号连接
    return OkBox();
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

auto JstpServer::initTcpSocket() -> ErrBox{
    /* 开启对TCP请求的监听 */
    if(!tcpserver_.listen(QHostAddress::Any, port_)){
        return ErrBox(ErrCode::TcpListen, "Failed to listen: "+ tcpserver_.errorString());
    }
    
    return OkBox();
}

auto JstpServer::initUdpSocket() -> ErrBox{
    auto ok = udpbroadcast_.bind(
        QHostAddress::Any,
        port_,
        QUdpSocket::ShareAddress
    );
    
    if(!ok){
        return ErrBox(ErrCode::UdpBind, "Failed to init broadcast: " + udpbroadcast_.errorString());
    }
    
    return OkBox();
}

auto JstpServer::initQConnections() -> void{
    connect(&tcpserver_, &QTcpServer::newConnection, this, &JstpServer::at_requestComing);
    connect(&udpbroadcast_, &QUdpSocket::readyRead, this, &JstpServer::at_broadcastComing);
}

void JstpServer::at_requestComing(){
    qDebug() << "Get TCP Request...";
}

void JstpServer::at_broadcastComing(){
    qDebug() << "Get UDP BroadCast...";
    
    auto netgram = udpbroadcast_.receiveDatagram();
    auto bytedata = netgram.data();
    qDebug() << "received " << bytedata.size() << " bytes";
    
    QDataStream ds(&bytedata, QIODevice::ReadOnly);
    ds.setByteOrder(QDataStream::LittleEndian);
    quint64 head_len;
    ds >> head_len;
    
    qDebug() << "length = " << head_len;
}


FILEDISC_END