#include "def/config.hpp"
#include "jstp/JstpClient.hpp"
#include "jstp/jobs/RequesHostJob.hpp"
FILEDISC_BEGIN

JstpClient::JstpClient()
    : threads_(MAX_THRAED, MAX_JOB)
    , port_(CLIENT_PORT)
    , jobid_(0)
{

}

auto JstpClient::initClient() -> ErrBox{
    return OkBox();
}

auto JstpClient::requestHost() -> Result<qint32>{
    return {-1, ErrBox(ErrCode::Busy, "")};
}

auto JstpClient::requestFile(const JstpHostField &host, 
    const QString &beginPath, const QString &targetName) -> Result<qint32>
{
    return {-1, ErrBox(ErrCode::Busy, "Job queue is full.")};
}

auto JstpClient::requestDir(const JstpHostField &host, 
    const QString &beginPath, const QString &targetName) -> Result<qint32>
{
    return {-1, ErrBox(ErrCode::Busy, "Job queue is full.")};
}

auto JstpClient::initBroadcast() -> ErrBox{
    return OkBox();
}

auto JstpClient::initHostsock() -> ErrBox{
    return OkBox();
}

auto JstpClient::initQConnections() -> void{
   
}

auto JstpClient::nextJobId() -> qint32{
    return jobid_++;
}

void JstpClient::at_hostComing(){
    qDebug() << "Get UDP response.";
}


FILEDISC_END