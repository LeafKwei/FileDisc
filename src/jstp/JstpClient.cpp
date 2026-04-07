#include "def/config.hpp"
#include "utility/StaticKit.hpp"
#include "jstp/JstpClient.hpp"
#include "jstp/jobs/ReqHostJob.hpp"
FILEDISC_BEGIN

JstpClient::JstpClient(const QString &name)
    : manager_(MAX_THRAED, MAX_JOB)
    , port_(CLIENT_PORT)
    , jobid_(0)
    , name_(name)
{
    
}

auto JstpClient::initClient() -> ErrBox{
    initQConnections();
    
    auto err = initLoalHost();
    if(err){
        return err;
    }
    
    err = initUdpReceiver();
    if(err){
        return err;
    }
    
    return OkBox();
}

auto JstpClient::requestHost() -> Result<qint32>{
    auto id = nextJobId();
    Job *req = new ReqHostJob(id, local_);
    if(req == nullptr){
        return Result<qint32>{-1, ErrBox{ErrCode::Memory, "Failed to alloc memories for ReqHostJob."}};
    }
    
    if(!manager_.sendToQueue(req)){
        return Result<qint32>{-1, ErrBox{ErrCode::Busy, "No memory or job queue is full."}};
    }
    
    return Result<qint32>{id, ErrBox{ErrCode::OK}};
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

auto JstpClient::initLoalHost() -> ErrBox{
    local_.name = name_;
    local_.ip = StaticKit::getLocalIpAddress();
    local_.port = port_;
    
    if(local_.ip == 0){
        return ErrBox{ErrCode::LocalNetwork, "No avaliable network interface or ip address."};    
    }
    
    return OkBox();
}

auto JstpClient::initUdpReceiver() -> ErrBox{
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