#ifndef JOB_HPP
#define JOB_HPP

#include <QObject>
#include "def/types.hpp"
#include "thread/RunnerInf.hpp"
class QThread;
FILEDISC_BEGIN
class QuitedJob;
class ThreadRunner;

/*///////// 任务接口，ThreadManager的用户需要自行实现此接口以便将任务交给前者执行 /////////*/
class Job : public QObject{
    Q_OBJECT
public:
    virtual ~Job() noexcept =default;
    virtual auto id() const noexcept -> qint32 =0;  //获取任务ID
    virtual auto run() -> ErrCode =0; //执行任务
    virtual auto moveMemberTo(QThread *thread) -> void =0; //移动Job中的QObject成员到线程中

private:
    /* cntl函数仅对一部分类型开放，所以将这些类型声明为友元 */
    friend class QuitedJob;
    friend class ThreadRunner;
    virtual auto cntl(RunnerInf &inf) -> void;    //对ThreadRunner进行控制
};

FILEDISC_END
#endif
