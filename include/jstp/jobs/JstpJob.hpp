#ifndef JSTPJOB_HPP
#define JSTPJOB_HPP

#include <QSharedPointer>
#include "thread/Job.hpp"
#include "jstp/JstpPayload.hpp"
FILEDISC_BEGIN

class JstpJob : public Job{
public:
    explicit JstpJob(quint32 id);

    auto isNull() -> bool;  //检查Job内部的payload是否分配成功
    auto payload() -> JstpPayload&; //获取payload的引用
    auto id() -> quint32 override;
    
private:
    quint32 id_;
    QSharedPointer<JstpPayload> payload_;
};

FILEDISC_END
#endif
