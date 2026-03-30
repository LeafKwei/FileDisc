#ifndef THREADRUNNER_HPP
#define THREADRUNNER_HPP

#include <QObject>
#include "def/types.hpp"
FILEDISC_BEGIN
class JobQueue;

/*///////// QThread线程会直接执行此对象的run函数而非任务，然后通过该函数依次执行任务队列中的任务 /////////*/
class ThreadRunner : public QObject{
    Q_OBJECT
public:
    explicit ThreadRunner(JobQueue &jobQueue);
    
private:
    JobQueue &jobQueue_;

signals:
    void to_jobstart(); //线程获取到任务并开始执行时
    void to_jobdone(); //线程将任务执行完毕后

public slots:
    void run();
};

FILEDISC_END
#endif
