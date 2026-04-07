#include <QUdpSocket>
#include "def/config.hpp"
#include "jstp/jstp.hpp"
#include "jstp/jobs/ReqHostJob.hpp"
FILEDISC_BEGIN

ReqHostJob::ReqHostJob(qint32 id)
    : JstpJob(id)
{

}

auto ReqHostJob::run() noexcept -> ErrCode{
    if(noPayload()){
        return ErrCode::JobInit;
    }
    
    QUdpSocket udpsock;
    JstpPayload &req = payload();
    
    /* 发送广播 */
    qint64 nwrite = udpsock.writeDatagram(req.toSendable(), QHostAddress::Broadcast, SERVER_PORT);
    if(nwrite < 0){
        return ErrCode::UdpSend;
    }
    
    return ErrCode::Ok;
}

FILEDISC_END