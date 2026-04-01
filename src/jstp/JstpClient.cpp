#include "def/config.hpp"
#include "jstp/JstpClient.hpp"
#include "jstp/jobs/RequesHostJob.hpp"
FILEDISC_BEGIN

JstpClient::JstpClient()
    : threads_(MAX_THRAED)
    , port_(CLIENT_PORT)
    , jobid_(0)
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

auto JstpClient::requestHost() -> Result<qint32>{
    /* 创建任务对象 */
    auto jobid = nextJobId();
    RequesHostJob *reqjob = new (std::nothrow) RequesHostJob(jobid, broadsock_);
    if(reqjob == nullptr || reqjob -> noPayload()){
        return {-1, ErrBox(ErrCode::JobInit, "Failed to alloc mem for job.")};
    }
    
    /* 初始化任务 */
    
    
    /* 发送任务到线程池 */
    if(!threads_.sendToQueue(reqjob)){
        delete reqjob; //虽然想用智能指针，但QT里貌似不适合用
        return {-1, ErrBox(ErrCode::Busy, "Job queue is full.")};
    }
    
    return {jobid, OkBox()};
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
    /* 初始化UDP广播套接字，后续会使用此套接字在局域网内向所有Server广播请求 */
    auto ok = broadsock_.bind(
        0,
        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint
    );
    
    if(!ok){
        return ErrBox(ErrCode::UDPBind, "Failed to init broadcast: " + broadsock_.errorString());
    }
    
    return OkBox();
}

auto JstpClient::initHostsock() -> ErrBox{
    /* 初始化用于监听Server响应的UDP套接字 */
    auto ok = hostsock_.bind(QHostAddress::Any, port_);
    if(!ok){
        return ErrBox(ErrCode::UDPBind, "Failed to init udp: " + hostsock_.errorString());
    }
    
    return OkBox();
}

auto JstpClient::initQConnections() -> void{
    connect(&hostsock_, SIGNAL(readyRead()), this, SLOT(at_hostComing()));
}

auto JstpClient::nextJobId() -> qint32{
    return jobid_++;
}

void JstpClient::at_hostComing(){
    qDebug() << "Get UDP response.";
}


FILEDISC_END