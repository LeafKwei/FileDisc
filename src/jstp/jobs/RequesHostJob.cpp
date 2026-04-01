#include "def/config.hpp"
#include "jstp/jobs/RequesHostJob.hpp"
FILEDISC_BEGIN

RequesHostJob::RequesHostJob(qint32 id, QUdpSocket &broadsock)
    : JstpJob(id)
    , broadsock_(broadsock)
{
    
}

auto RequesHostJob::run() -> void{
    auto ba = payload().toSendable();
    auto nwrite = broadsock_.writeDatagram(
        ba,
        QHostAddress::Broadcast,
        SERVER_PORT
    );
    
    ErrCode err = (nwrite < 0) ? ErrCode::BroCasSend : ErrCode::OK;
    emit to_requestHostJobDone(id(), err);
}

FILEDISC_END