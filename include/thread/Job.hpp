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
    virtual auto run() -> ErrCode =0; //执行任务
    virtual auto moveMemberTo(QThread *thread) -> void =0; //移动Job中的QObject成员到线程中
};

FILEDISC_END
#endif
