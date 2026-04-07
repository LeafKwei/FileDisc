#include "def/config.hpp"
#include "utility/StaticKit.hpp"
#include "jstp/JstpClient.hpp"
#include "jstp/jobs/ReqHostJob.hpp"
#include "jstp/jobs/ReqFileJob.hpp"
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
    /* 生成Job并检查是否可用 */
    auto id = nextJobId();
    JstpJob *job = new (std::nothrow) ReqHostJob(id);
    if(isBadJob(job)){
        delete job;
        return Result<qint32>{-1, ErrBox{ErrCode::Memory, "Failed to alloc memories for ReqHostJob."}}; 
    }
    
    /* 填充请求 */
    fillHostReq(job -> payload());
    
    /* 发送Job到任务队列执行 */
    return submit(job);
}

auto JstpClient::requestFile(const JstpHostField &server, 
    const QString &beginPath, const QString &targetName) -> Result<qint32>
{
    auto id = nextJobId();
    JstpJob *job = new (std::nothrow) ReqFileJob(id, server);
    if(isBadJob(job)){
        delete job;
        return Result<qint32>{-1, ErrBox{ErrCode::Memory, "Failed to alloc memories for ReqHostJob."}}; 
    }
    
    fillFileReq(job -> payload());
    return submit(job);
}

auto JstpClient::requestDir(const JstpHostField &server, 
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

auto JstpClient::submit(JstpJob *job) -> Result<qint32>{
    if(!manager_.sendToQueue(job)){
        return Result<qint32>{-1, ErrBox{ErrCode::Busy, "No memory or job queue is full."}};
    }
    
    return Result<qint32>{job -> id(), ErrBox{ErrCode::Ok}};
}

auto JstpClient::isBadJob(JstpJob *job) -> bool{
    return (job == nullptr || job -> noPayload());
}

auto JstpClient::fillHostReq(JstpPayload &req) -> ErrBox{
    /* 填充报文 */
    req.setPair(JSTP_TYPE, QString::number(static_cast<qint32>(ReqType::HostInfo))); //请求Server的主机信息
    req.setHostField(local_);  //Client的主机信息
    return OkBox();
}

auto JstpClient::fillFileReq(JstpPayload &req) -> ErrBox{
    return OkBox();
}

void JstpClient::at_hostComing(){
    qDebug() << "Get UDP response.";
}


FILEDISC_END