#include <QTcpSocket>
#include "def/config.hpp"
#include "jstp/jstp.hpp"
#include "jstp/jobs/ReqFileJob.hpp"
FILEDISC_BEGIN

ReqFileJob::ReqFileJob(qint32 id, JstpHostField server)
    : JstpJob(id)
    , server_(server)
{

}

auto ReqFileJob::run() noexcept -> ErrCode{
    if(noPayload()){
        return ErrCode::JobInit;
    }
    
    QTcpSocket tcpsock;
    tcpsock.connectToHost(QHostAddress(server_.ip), server_.port);
    auto ok = tcpsock.waitForConnected(5000); //等待5s
    if(ok){
        qDebug() << "Ok to connected server.";
    }
    else{
        qDebug() << "Failed to connected server.";
        return ErrCode::TcpConne;
    }
    
    return ErrCode::Ok;
}

FILEDISC_END