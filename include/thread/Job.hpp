#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include "def/types.hpp"
FILEDISC_BEGIN

class Job : public QObject{
    Q_OBJECT
public:
    virtual auto id() const noexcept -> qint32 =0;  //获取任务ID
    virtual auto run() -> Result<QVariant> =0; //执行任务
};

using JobPtr = QSharedPointer<Job>;

FILEDISC_END
#endif
