#ifndef MANAGERINF_HPP
#define MANAGERINF_HPP

#include "def/types.hpp"
FILEDISC_BEGIN

class ManagerInf{
public:
    auto countFreeThreads() const noexcept -> qint32;  //获取空闲的线程数量
    auto setFreeThreadsCount(qint32 val) noexcept -> void;
    
private:

};

FILEDISC_END
#endif
