#include <QMutexLocker>
#include "thread/JobQueue.hpp"
FILEDISC_BEGIN

JobQueue::JobQueue(qint32 max) 
    : max_(max)
{
    
}

auto JobQueue::append(Job *job) -> bool{
    /* 任务数量达到上限 */
    if(jobs_.size() >= max_){
        return false;
    }
    
    /* 添加任务并唤醒一个线程 */
    QMutexLocker locker(&mutex_);
    jobs_.push_back(job);
    cond_hasjob_.notify_one();

    return true;
}

auto JobQueue::obtain() -> Job*{
    /* 尝试获取一个任务，如果队列为空，则等待 */
    QMutexLocker locker(&mutex_);
    while(jobs_.isEmpty()){
        cond_hasjob_.wait(&mutex_);
    }
    
    /* 获取任务并返回 */
    Job *job = jobs_.first();
    jobs_.erase(jobs_.cbegin()); //将任务从队列移除
    return job;
}

FILEDISC_END