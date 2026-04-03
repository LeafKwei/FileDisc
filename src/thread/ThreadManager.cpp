#include <QThread>
#include "def/config.hpp"
#include "thread/Job.hpp"
#include "thread/ThreadManager.hpp"
FILEDISC_BEGIN

ThreadManager::ThreadManager(qint32 maxthrs, qint32 maxjobs)
    : maxthrs_(maxthrs)
    , maxjobs_(maxjobs)
{

}

ThreadManager::~ThreadManager() noexcept{
    /* 删除所有未执行的任务 */
    for(auto *job : pendjobs_){
        delete job;
    }
    
    /* 当线程结束时，删除线程 */
    for(auto *thread : threads_){
        connect(thread, &QThread::finished, 
            thread, &QThread::deleteLater, Qt::DirectConnection); 
    }
}

auto ThreadManager::sendToQueue(Job *job) -> bool{
    return execJob(job);
}

auto ThreadManager::execJob(Job *job) -> bool{
    /* 创建线程 */
    QThread *thread = createThread();
    
    /* 无可用线程时，将Job缓存到待决队列 */
    if(thread == nullptr){
        return appendPendJob(job);
    }
    
    /* 连接信号和槽，随后启动线程执行Job */
    connectEntity(thread, job);
    job -> moveToThread(thread);
    job -> moveMemberTo(thread);
    thread -> start();
    return true;
}

auto ThreadManager::appendPendJob(Job *job) -> bool{
    if(pendjobs_.size() >= maxjobs_){ //待决Job数量达到上限时，停止增加Job
        return false;
    }
    
    pendjobs_.push_back(job);
    return true;
}

auto ThreadManager::createThread() -> QThread*{
    if(threads_.size() >= maxthrs_){  //线程数量达到上限时，停止创建线程
        return nullptr;
    }
    
    QThread *thread = new (std::nothrow) QThread;
    if(thread == nullptr){
        return nullptr;
    }
    
    threads_.push_back(thread);
    return thread;
}

auto ThreadManager::connectEntity(QThread *thread, Job *job) -> void{    
    connect(thread, &QThread::started), 
        job, &Job::run, Qt::DirectConnection); //线程启动时，执行run
    connect(thread, &QThread::finished), 
        job, &Job::deleteLater, Qt::DirectConnection); //线程结束时，销毁Job
    connect(thread, &QThread::finished), 
        thread, &QThread::deleteLater, Qt::DirectConnection); //线程结束时，销毁线程自身
    connect(job, &Job::to_threadQuit, 
        thread, &QThread::quit, Qt::DirectConnection); //Job完成时，退出线程
    connect(job, &Job::to_jobFinished, 
        this, &ThreadManager::at_jobFinished, Qt::QueuedConnection); //Job完成时，将Job的指针从exec队列中移除
}

auto ThreadManager::removeFinishedThread() -> void{
    auto cbegin = threads_.cbegin();
    auto cend = threads_.cend();
    
    while(cbegin != cend){
        if(cbegin -> isFinished()){
            qDebug() << "size before remove thread pointer: " << threads_.size();
            cbegin = threads_.erase(cbegin);
            qDebug() << "size after remove thread pointer: " << threads_.size();
        }
    }
}

void ThreadManager::at_jobFinished(qint32 jobid){
    /* 发送任务已完成的信号 */
    emit at_jobFinished(jobid);
    
    /* 移除已经finished的线程 */
    removeFinishedThread();
    
    /* 从待决队列中取出新的Job执行 */
    if(pendjobs_.isEmpty()){
        return;
    }
    
    Job *job = pendjobs_.front();
    pendjobs_.pop_front();
    execJob(job);
}

FILEDISC_END