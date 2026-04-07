#ifndef JSTPJOB_HPP
#define JSTPJOB_HPP

#include <QSharedPointer>
#include "thread/Job.hpp"
#include "jstp/JstpPayload.hpp"
#include "jstp/JstpEmiter.hpp"
FILEDISC_BEGIN

class JstpJob : public Job{
public:
    explicit JstpJob(qint32 id);
    auto noPayload() -> bool;  //检查Job内部的payload是否分配成功
    auto payload() -> JstpPayload&; //获取payload的引用
    auto emiter() -> JstpEmiter&;   //获取emiter的引用
    auto id() const noexcept -> qint32 override;
    
private:
    qint32 id_;
    JstpEmiter emiter_;
    QSharedPointer<JstpPayload> payload_;
};

FILEDISC_END
#endif
