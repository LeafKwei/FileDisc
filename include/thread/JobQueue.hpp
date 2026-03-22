#ifndef JOBQUEUE_HPP
#define JOBQUEUE_HPP

#include <QMutex>
#include <QWaitCondition>
#include <QVector>
#include "def/types.hpp"
#include "thread/Job.hpp"
FILEDISC_BEGIN

class JobQueue{
public:
    explicit JobQueue() =default;
    auto append(JobPtr job) -> bool; //添加任务到队列尾部，同时唤醒一个线程
    auto obtain() -> JobPtr; //获取队列首个任务，队列为空则阻塞当前线程

private:
    QMutex mutex_;
    QWaitCondition cond_hasjob_;  //消费者线程在任务队列为空时，在此条件上等待
    QVector<JobPtr> jobs_;
};

FILEDISC_END
#endif
