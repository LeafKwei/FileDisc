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
    
    /* 停止所有线程，随后删除 */
    for(auto *thread : threads_){
        thread -> quit();
        thread -> wait();
        delete thread;
    }
}

auto ThreadManager::sendToQueue(Job *job) -> bool{
    return execJob(job);
}

auto ThreadManager::execJob(Job *job) -> bool{
    /* 寻找是否存在空闲线程，如果没有则创建 */
    QThread *thread = findFreeThread();
    
    /* 无空闲线程时，将Job缓存到待决队列 */
    if(thread == nullptr){
        return appendPendJob(job);
    }
    
    /* 连接信号和槽，随后启动线程并将Job添加到执行队列 */
    connectEntity(thread, job);
    job -> moveToThread(thread);
    job -> moveMemberTo(thread);
    thread -> start();
    appendExecJob(job);
    return true;
}

auto ThreadManager::appendExecJob(Job *job) -> bool{
    execjobs_.push_back(job);
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

/* 尝试寻找已经finished的线程执行Job，如果没有，则调用createThread创建线程 */
auto ThreadManager::findFreeThread() -> QThread*{
    for(int idx = 0; idx < threads_.size(); idx++){
        QThread *thread = threads_.at(idx);
        if(thread -> isFinished()){
            (thread -> wait(100)) ? thread : nullptr; //等待线程完全结束(至多100ms))
        }
    }
    
    return createThread();
}

auto ThreadManager::connectEntity(QThread *thread, Job *job) -> void{
    thread -> disconnect();
    connect(thread, SIGNAL(started()), job, SLOT(run())); //线程启动时，执行run
    connect(thread, SIGNAL(finished()), job, SLOT(deleteLater())); //线程结束时，销毁Job
    connect(job, SIGNAL(to_threadQuit()), thread, SLOT(quit())); //Job完成时，退出线程
    connect(job, SIGNAL(to_jobFinished(void*)), this, SLOT(at_jobFinished(void*))); //Job完成时，将Job的指针从exec队列中移除
}

void ThreadManager::at_jobFinished(void *addr){
    /* 移除exec队列中已完成的Job */
    execjobs_.remove((QThread*)addr);
    
    /* 从待决队列中取出新的Job执行 */
    if(pendjobs_.isEmpty()){
        return;
    }
    
    Job *job = pendjobs_.front();
    pendjobs_.pop_front();
    execJob(job);
}

FILEDISC_END