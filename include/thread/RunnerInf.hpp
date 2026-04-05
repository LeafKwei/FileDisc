#ifndef RUNNERINF_HPP
#define RUNNERINF_HPP

#include "def/version.hpp"
FILEDISC_BEGIN

/*///////// ThreadRunner的信息对象，记录控制标志等信息 /////////*/
class RunnerInf{
public:
    RunnerInf();
    auto shouldQuit() const noexcept -> bool;   //获取退出标志
    auto setFlagQuit(bool v) noexcept -> void;  //设置退出标志
    
private:
    bool flagQuit_;
};

FILEDISC_END
#endif
