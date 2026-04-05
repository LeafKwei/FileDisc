#ifndef JOBQUEUE_HPP
#define JOBQUEUE_HPP

#include <QMutex>
#include <QWaitCondition>
#include <QVector>
#include <atomic>
#include "def/types.hpp"
#include "thread/Job.hpp"
FILEDISC_BEGIN

/*///////// 任务队列，发送给ThreadManager的任务会缓存到此队列，然后由线程依次取出执行 /////////*/
class JobQueue{
public:
    explicit JobQueue(qint32 max);
    ~JobQueue() noexcept;
    auto append(Job *job) -> bool; //添加任务到队列尾部，同时唤醒一个线程(任务执行完毕后会自动销毁)
    auto obtain() -> Job*; //获取队列首个任务，队列为空则阻塞当前线程

private:
    qint32 max_;
    QMutex mutex_;
    QWaitCondition cond_hasjob_;  //消费者线程在任务队列为空时，在此条件上等待
    QVector<Job*> jobs_;
};

FILEDISC_END
#endif
