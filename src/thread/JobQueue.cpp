#include <QMutexLocker>
#include "thread/JobQueue.hpp"
FILEDISC_BEGIN

JobQueue::JobQueue(qint32 max) 
    : useable_{true}
    , max_(max)
{
    
}

JobQueue::~JobQueue() noexcept{
    mutex_.lock();
    useable_ = false;
    mutex_.unlock();
    
    /* 删除所有未执行的任务 */
    auto begin = jobs_.begin();
    auto end = jobs_.end();
    
    for(; begin != end; begin++){
        delete *(begin);
    }
}

auto JobQueue::append(Job *job) -> bool{
    /* 双重检测(锁前所后)，避免多线程环境下有线程在此对象析构时访问 */
    if(!useable_){
        return false;
    }
    
    /* 任务数量达到上限 */
    if(jobs_.size() >= max_){
        return false;
    }
    
    /* 添加任务并唤醒一个线程 */
    QMutexLocker locker(&mutex_);
    
    if(!useable_){
        return false;
    }
    
    jobs_.push_back(job);
    cond_hasjob_.notify_one();

    return true;
}

auto JobQueue::obtain() -> Job*{
    /* 双重检测(锁前所后)，避免多线程环境下有线程在此对象析构时访问 */
    if(!useable_){
        return nullptr;
    }
    
    /* 尝试获取一个任务，如果队列为空，则等待 */
    QMutexLocker locker(&mutex_);
    
    if(!useable_){
        return nullptr;
    }
    
    while(jobs_.isEmpty()){
        cond_hasjob_.wait(&mutex_);
    }
    
    /* 获取任务并返回 */
    Job *job = jobs_.first();
    jobs_.erase(jobs_.cbegin()); //将任务从队列移除
    return job;
}

FILEDISC_END