#include "thread/ManagerInf.hpp"
FILEDISC_BEGIN

auto ManagerInf::countFreeThreads() const noexcept -> qint32{
    return threadcnt_;
}

auto ManagerInf::setFreeThreadsCount(qint32 val) noexcept -> void{
    threadcnt_ = val;
}

FILEDISC_END