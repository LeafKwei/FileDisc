#include <QThread>
#include "def/config.hpp"
#include "thread/jobs/CntledJob.hpp"
#include "thread/ThreadRunner.hpp"
#include "thread/ThreadManager.hpp"
FILEDISC_BEGIN

ThreadManager::ThreadManager(qsizetype maxthrds, qsizetype maxjobs) 
    : maxthrds_(maxthrds)
    , maxjobs_(maxjobs)
    , inf_{}
    , jobqptr_(nullptr)
{
    jobqptr_.reset(new JobQueue(maxjobs_));
    assert(!(jobqptr_.isNull()) && "Failed to alloc memories for job queue.");
}

/**
 * 注意，为了确保在析构时，所有的QThread能够被销毁，Job的实现者需要确保：
 * 1.run函数不抛出任何异常
 * 2.run函数一定会返回
 */
ThreadManager::~ThreadManager() noexcept{
    /* 清空队列中未执行的任务 */
    jobqptr_ -> clean();

    /* 遍历所有线程，调用quit函数，同时每有一个线程，就向JobQueue中添加一个CntledJob，以便结束ThreadRunner */
    auto end = threads_.end();
    for(auto it = threads_.begin(); it != end; it++){
        it -> first -> quit();
        jobqptr_ -> append(new CntledJob);
    }
}

auto ThreadManager::sendToQueue(Job *job) -> bool{
    if(inf_.countFreeThreads() == 0){  //如果没有空闲线程，则创建新线程
        createThread();
    }
    
    auto result = jobqptr_ -> append(job);
    return result;
}

auto ThreadManager::info() const noexcept -> RoInfo{
    return inf_;
}

auto ThreadManager::createThread() -> void{
    if(threads_.size() >= maxthrds_){  //线程数量达到上限时，不再创建线程
        return;
    }
    
    QThread *thread = new QThread;
    ThreadRunner *runner = new ThreadRunner(jobqptr_);
    if(thread == nullptr || runner == nullptr){ //内存分配失败时，直接返回
        delete thread;
        delete runner;
        return;
    }
    
    /* 将线程与runner对象建立连接 */
    runner -> moveToThread(thread);
    connect(thread, &QThread::started, runner, &ThreadRunner::run, Qt::DirectConnection);
    
    /* 启用延时删除，避免内存泄漏和提前释放问题 */
    connect(thread, &QThread::finished, runner, &ThreadRunner::deleteLater, Qt::DirectConnection);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater, Qt::QueuedConnection);
    
    /* 更新Manager信息 */
    updateManager(thread, runner);
    
    /* 启动线程 */
    thread -> start();
}

auto ThreadManager::updateManager(QThread *thread, ThreadRunner *runner) -> void{
    connect(runner, &ThreadRunner::to_jobStart, this, &ThreadManager::at_jobStart, Qt::QueuedConnection);
    connect(runner, &ThreadRunner::to_jobDone, this, &ThreadManager::at_jobDone, Qt::QueuedConnection);
    
    inf_.setFreeThreadsCount(inf_.countFreeThreads() + 1);
    threads_.push_back({thread, runner});
}

void ThreadManager::at_jobStart(qint32 jobid){
    inf_.setFreeThreadsCount(inf_.countFreeThreads() - 1);
}

void ThreadManager::at_jobDone(qint32 jobid, ErrCode err){
    emit to_jobFinished(jobid, err);
    inf_.setFreeThreadsCount(inf_.countFreeThreads() + 1);
}



FILEDISC_END