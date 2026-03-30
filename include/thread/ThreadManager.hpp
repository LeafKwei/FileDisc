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

/*///////// 创建和管理线程，用户可将任务发送给此对象以便由线程执行 /////////*/
class ThreadManager : public QObject{
    Q_OBJECT
public:
    using RoInfo = ManagerInf;
    using ThreadVector = QVector<QPair<QThread*, ThreadRunner*>>;

public:
    explicit ThreadManager(qint32 max);
    auto sendToQueue(Job *job) -> bool; //发送任务到任务队列中，如果任务数量已达到上限，则返回false; Job会通过调用deleteLater自动删除，需要确保创建该Job的线程运行了事件循环
    auto info() const noexcept -> RoInfo; //返回ManagerInfo的只读引用

private:
    auto createThread() -> void;
    auto updateManager(QThread *thread, ThreadRunner *runner) -> void;

private:
    qint32 max_;
    ManagerInf inf_;
    JobQueue jobQueue_;
    ThreadVector threads_;
    
public slots:
    void at_jobstart();
    void at_jobdone();
};

FILEDISC_END
#endif
