#include "jstp/jobs/JstpJob.hpp"
FILEDISC_BEGIN

JstpJob::JstpJob(quint32 id) 
    : id_(id)
{
    /* 如果内存分配出错，则首先捕获异常，然后将指针显式置空 */
    try{
        payload_ = new JstpPayload;
    }catch(std::exception &e){
        payload_ = nullptr;
    }
}

auto JstpJob::isNull() -> bool{
    return payload_ == nullptr;
}

auto JstpJob::payload() -> JstpPayload&{
    return *payload_;
}

auto JstpJob::id() -> quint32 override{
    return quint32;
}

FILEDISC_END