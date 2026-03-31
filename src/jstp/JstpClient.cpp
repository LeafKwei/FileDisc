#include "def/config.hpp"
#include "jstp/JstpClient.hpp"
FILEDISC_BEGIN

JstpClient::JstpClient()
    : port_(CLIENT_PORT)
{

}

auto JstpClient::listen() -> ErrBox{
    /* 初始化信号连接 */
    initQConnections();
    
    /* 开启主机信息socket的监听 */
    auto err = initHostsock();
    if(err){
        return err;
    }
    
    return OkBox();
}

auto JstpClient::broadcastToLAN() -> ErrBox{
    QUdpSocket broadcast;
    
    /* 初始化广播 */
    auto err = initBroadcast(broadcast);
    if(err){
        return err;
    }
    
    /* 构建请求 */
    makeHostRequest();
    
    /* 发送广播 */
    err = sendHostRequest(0);
    if(err){
        return err;
    }
    
    return OkBox();
}

auto JstpClient::request(ArgHolder) -> Result<quint32>{
    return Result<quint32>{0, ErrBox()};
}

auto JstpClient::setPort(qint16 port) -> void{
    port_ = port;
}

auto JstpClient::sendHostRequest(ArgHolder) -> ErrBox{
    return OkBox();
}

auto JstpClient::makeHostRequest() -> ArgHolder{
    return {};
}

auto JstpClient::initBroadcast(QUdpSocket &broadcast) -> ErrBox{
    auto ok = broadcast.bind(
        0,
        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint
    );
    
    if(!ok){
        return ErrBox(ErrCode::UDPBind, "Failed to bind: " + broadcast.errorString());
    }
    
    return OkBox();
}

auto JstpClient::initHostsock() -> ErrBox{
    return OkBox();
}

auto JstpClient::initQConnections() -> void{
    
}

void JstpClient::at_hostComing(){

}


FILEDISC_END