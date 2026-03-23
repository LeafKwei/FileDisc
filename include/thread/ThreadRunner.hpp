#ifndef THREADRUNNER_HPP
#define THREADRUNNER_HPP

#include <QObject>
#include "def/types.hpp"
FILEDISC_BEGIN
class JobQueue;

class ThreadRunner : public QObject{
    Q_OBJECT
public:
    explicit ThreadRunner(JobQueue &jobQueue);
    
private:
    JobQueue &jobQueue_;

public slots:
    auto run() -> void;
    
signals:
    void to_jobstart(qint32 jobid); //线程获取到任务并开始执行时
    void to_jobdone(qint32 jobid, Result<QVariant> result); //线程将任务执行完毕后
};

FILEDISC_END
#endif
