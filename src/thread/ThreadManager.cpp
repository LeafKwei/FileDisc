#include <QThread>
#include "def/config.hpp"
#include "thread/ThreadRunner.hpp"
#include "thread/ThreadManager.hpp"
FILEDISC_BEGIN

ThreadManager::ThreadManager(qint32 max) 
    : max_(max)
    , inf_{}
    , jobQueue_(MAX_JOB)
{

}

auto ThreadManager::sendToQueue(Job *job) -> bool{
    if(inf_.countFreeThreads() == 0){  //如果没有空闲线程，则创建新线程
        createThread();
    }
    
    auto result = jobQueue_.append(job);
    return result;
}

auto ThreadManager::info() const noexcept -> RoInfo{
    return inf_;
}

auto ThreadManager::createThread() -> void{
    if(threads_.size() >= max_){  //线程数量达到上限时，不再创建线程
        return;
    }
    
    QThread *thread = new QThread;
    ThreadRunner *runner = new ThreadRunner(jobQueue_);
    if(thread == nullptr || runner == nullptr){ //内存分配失败时，直接返回
        delete thread;
        delete runner;
        return;
    }
    
    /* 将线程与runner对象建立连接 */
    runner -> moveToThread(thread);
    connect(thread, SIGNAL(started()), runner, SLOT(run()));
    
    /* 启用延时删除，避免内存泄漏和提前释放问题 */
    connect(thread, SIGNAL(finished()), runner, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    
    /* 更新Manager信息 */
    updateManager(thread, runner);
    
    /* 启动线程 */
    thread -> start();
}

auto ThreadManager::updateManager(QThread *thread, ThreadRunner *runner) -> void{
    connect(runner, SIGNAL(to_jobstart()), this, SLOT(at_jobstart()));
    connect(runner, SIGNAL(to_jobdone()), this, SLOT(at_jobdone()));
    
    inf_.setFreeThreadsCount(inf_.countFreeThreads() + 1);
    threads_.push_back({thread, runner});
}

void ThreadManager::at_jobstart(){
    inf_.setFreeThreadsCount(inf_.countFreeThreads() - 1);
}

void ThreadManager::at_jobdone(){
    inf_.setFreeThreadsCount(inf_.countFreeThreads() + 1);
}



FILEDISC_END