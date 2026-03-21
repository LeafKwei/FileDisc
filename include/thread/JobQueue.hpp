#ifndef JOBQUEUE_HPP
#define JOBQUEUE_HPP

#include <QMutex>
#include <QMutexLocker>
#include <QVector>
#include "def/types.hpp"
#include "thread/ThreadJob.hpp"
FILEDISC_BEGIN

class JobQueue{
public:
    explicit JobQueue();
    void appendJob();
    void obtainJob();
    void countJob() const;
    

private:
    QMutex mutex_;
    QVector<ThreadJobPtr> jobs_;
};

FILEDISC_END
#endif
