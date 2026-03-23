#ifndef MANAGERINF_HPP
#define MANAGERINF_HPP

#include "def/types.hpp"
FILEDISC_BEGIN

class ManagerInf{
public:
    explicit ManagerInf() =default;
    auto countFreeThreads() const noexcept -> qint32;  //获取空闲的线程数量
    auto setFreeThreadsCount(qint32 val) noexcept -> void;
    
private:
    qint32 threadcnt_;
};

FILEDISC_END
#endif
