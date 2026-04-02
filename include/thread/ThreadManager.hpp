#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include <QObject>
#include <QVector>
#include "def/types.hpp"
class QThread;

FILEDISC_BEGIN
class Job;

/*///////// 创建和管理线程，用户可将任务发送给此对象以便由线程执行 /////////*/
class ThreadManager : public QObject{
    Q_OBJECT
public:
    using JobQueue = QVector<Job*>;
    using ThreadVector = QVector<QThread*>;

public:
    explicit ThreadManager(qint32 maxthrs, qint32 maxjobs);
    ~ThreadManager() noexcept;
    auto sendToQueue(Job *job) -> bool; //发送任务到任务队列中，如果任务数量已达到上限，则返回false; Job会通过调用deleteLater自动删除

private:
    auto execJob(Job *job) -> bool;
    auto appendExecJob(Job *job) -> bool;
    auto appendPendJob(Job *job) -> bool;
    auto createThread() -> QThread*;
    auto findFreeThread() -> QThread*;    
    auto connectEntity(QThread *thread, Job *job) -> void;

private:
    qint32 maxthrs_;
    qint32 maxjobs_;
    JobQueue execjobs_;  //正在执行的任务
    JobQueue pendjobs_;  //准备执行的任务
    ThreadVector threads_;
    
public slots:
    void at_jobFinished(void *addr);
};

FILEDISC_END
#endif
