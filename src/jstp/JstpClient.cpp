#include "def/config.hpp"
#include "jstp/JstpClient.hpp"
FILEDISC_BEGIN

JstpClient::JstpClient()
    : port_(CLIENT_PORT)
{

}

auto JstpClient::initClient() -> ErrBox{
    initQConnections(); //初始化信号连接
    auto err = initHostsock();
    if(err){
        return err;
    }
    
    err = initBroadcast();
    if(err){
        return err;
    }
    
    return OkBox();
}

auto JstpClient::requestHost() -> Result<quint32>{
    
}

auto JstpClient::requestFile(const JstpHostField &host, 
    const QString &beginPath, const QString &targetName) -> Result<quint32>
{
    
}

auto JstpClient::requestDir(const JstpHostField &host, 
    const QString &beginPath, const QString &targetName) -> Result<quint32>
{

}

auto JstpClient::initBroadcast() -> ErrBox{
    /* 初始化UDP广播套接字，后续会使用此套接字在局域网内向所有Server广播请求 */
    auto ok = broadsock_.bind(
        0,
        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint
    );
    
    if(!ok){
        return ErrBox(ErrCode::UDPBind, "Failed to init broadcast: " + broadcast.errorString());
    }
    
    return OkBox();
}

auto JstpClient::initHostsock() -> ErrBox{
    /* 初始化用于监听Server响应的UDP套接字 */
    auto ok = hostsock_.bind(QHostAddress::Any, port_);
    if(!ok){
        return ErrBox(ErrCode::UDPBind, "Failed to init udp: " + hostsock_.errorString());
    }
}

auto JstpClient::initQConnections() -> void{
    connect(&hostsock_, SIGNAL(readyRead()), this, SLOT(at_hostComing()));
}

void JstpClient::at_hostComing(){
    qDebug() << "Get UDP response.";
}


FILEDISC_END