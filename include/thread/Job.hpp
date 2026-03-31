#ifndef JOB_HPP
#define JOB_HPP

#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include "def/types.hpp"
FILEDISC_BEGIN

/*///////// 任务接口，ThreadManager的用户需要自行实现此接口以便将任务交给前者执行 /////////*/
class Job : public QObject{
    Q_OBJECT
public:
    virtual ~Job() noexcept =default;
    virtual auto id() const noexcept -> qint32 =0;  //获取任务ID
    virtual auto run() -> void =0; //执行任务
};

FILEDISC_END
#endif
