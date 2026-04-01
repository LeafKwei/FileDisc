#include "jstp/jobs/JstpJob.hpp"
FILEDISC_BEGIN

JstpJob::JstpJob(qint32 id) 
    : id_(id)
{
    payload_ = QSharedPointer<JstpPayload>::create(); //用户在使用前需通过noPayload检查是否可用
}

auto JstpJob::noPayload() -> bool{
    return payload_ == nullptr;
}

auto JstpJob::payload() -> JstpPayload&{
    return *payload_;
}

auto JstpJob::id() const noexcept -> qint32{
    return id_;
}

FILEDISC_END