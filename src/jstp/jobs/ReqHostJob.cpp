#include <QUdpSocket>
#include "jstp/jstp.hpp"
#include "jstp/jobs/ReqHostJob.hpp"
FILEDISC_BEGIN

ReqHostJob::ReqHostJob(qint32 id, JstpHostField local)
    : JstpJob(id)
    , local_(local)
{

}

auto ReqHostJob::run() noexcept -> ErrCode{
    if(noPayload()){
        return ErrCode::JobInit;
    }
    
    QUdpSocket udpsock;
    JstpPayload &req = payload();
    
    /* 填充报文 */
    req.setPair(JSTP_TYPE, QString::number(static_cast<qint32>(ReqType::HostInfo))); //请求Server的主机信息
    req.setHostField(local_);  //Client的主机信息
    
    /* 发送广播 */
    qint64 nwrite = udpsock.writeDatagram(req.toSendable(), QHostAddress::Broadcast, local_.port);
    if(nwrite < 0){
        return ErrCode::UdpSend;
    }
    
    return ErrCode::OK;
}

FILEDISC_END