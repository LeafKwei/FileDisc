#ifndef JOB_HPP
#define JOB_HPP

#include <QObject>
#include "def/types.hpp"
class QThread;

FILEDISC_BEGIN

/*///////// 任务接口，ThreadManager的用户需要自行实现此接口以便将任务交给前者执行 /////////*/
class Job : public QObject{
    Q_OBJECT
public:
    virtual ~Job() noexcept =default;
    virtual auto id() const noexcept -> qint32 =0;  //获取任务ID
    virtual auto moveMemberTo(QThread *thread) -> void =0; //移动自身的成员到线程
    
signals:
    void to_threadQuit(); //当任务完成时，发出此信号以便退出线程，使之进入finished状态
    void to_jobFinished(void *addr); //当任务完成时，发出此信号以便ThreadManager可以取出其他任务执行，addr是Job的地址，提供给ThreadManager以便从List中移除Job

public slots:
    virtual auto run() -> void =0; //执行任务
};

FILEDISC_END
#endif
