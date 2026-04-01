#ifndef JSTPJOB_HPP
#define JSTPJOB_HPP

#include <QSharedPointer>
#include "thread/Job.hpp"
#include "jstp/JstpPayload.hpp"
FILEDISC_BEGIN

class JstpJob : public Job{
    Q_OBJECT
public:
    explicit JstpJob(qint32 id);
    auto noPayload() -> bool;  //检查Job内部的payload是否分配成功
    auto payload() -> JstpPayload&; //获取payload的引用
    auto id() const noexcept -> qint32 override;
    
private:
    qint32 id_;
    QSharedPointer<JstpPayload> payload_;
};

FILEDISC_END
#endif
