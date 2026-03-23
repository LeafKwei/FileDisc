#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include <QObject>
#include <QPair>
#include <QVector>
#include <QSharedPointer>
#include "def/types.hpp"
#include "thread/JobQueue.hpp"
#include "thread/ManagerInf.hpp"
class QThread;

FILEDISC_BEGIN
class ThreadRunner;

class ThreadManager : public QObject{
    Q_OBJECT
public:
    using RoInfo = ManagerInf;
    using ThreadVector = QVector<QPair<QThread*, ThreadRunner*>>;

public:
    explicit ThreadManager(qint32 max);
    auto sendToQueue(JobPtr job) -> bool; //发送任务到任务队列中，如果任务数量已达到上限，则返回false
    auto info() const noexcept -> RoInfo; //返回ManagerInfo的只读引用

private:
    auto createThread() -> void;
    auto updateManager(QThread *thread, ThreadRunner *runner) -> void;

private:
    qint32 max_;
    ManagerInf inf_;
    JobQueue jobQueue_;
    ThreadVector threads_;
    
signals:
    void to_jobreturn(qint32 jobid, Result<QVariant> result);
    
private slots:
    void at_jobstart(qint32 jobid);
    void at_jobdone(qint32 jobid, Result<QVariant> result);
};

FILEDISC_END
#endif
