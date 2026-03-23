#include <QMutexLocker>
#include "thread/JobQueue.hpp"
FILEDISC_BEGIN

JobQueue::JobQueue(qint32 max) : max_(max)
{
    
}

auto JobQueue::append(JobPtr job) -> bool{
    /* 任务数量达到上限 */
    if(jobs_.size() >= max_){
        return false;
    }
       if(job == nullptr) qDebug() << "Fuckkkkk4!";
    /* 添加任务并唤醒一个线程 */
    QMutexLocker locker(&mutex_);
    jobs_.push_back(job);
    cond_hasjob_.notify_one();

    return true;
}

auto JobQueue::obtain() -> JobPtr{
    /* 尝试获取一个任务，如果队列为空，则等待 */
    QMutexLocker locker(&mutex_);
    while(jobs_.isEmpty()){
        cond_hasjob_.wait(&mutex_);
    }
    
    /* 获取任务并返回 */
    JobPtr job = jobs_.first();  //注意，此处不能使用auto，first返回的是引用，如果使用auto，则job就是一个引用，不会增加引用计数，那么当erase元素后，智能指针指向的job就直接释放了
    jobs_.erase(jobs_.cbegin()); //将任务从队列移除
    return job;
}

FILEDISC_END