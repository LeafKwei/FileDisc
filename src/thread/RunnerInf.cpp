#include "thread/RunnerInf.hpp"
FILEDISC_BEGIN

RunnerInf::RunnerInf()
    : flagQuit_(false)
{

}

auto RunnerInf::shouldQuit() const noexcept -> bool{
    return flagQuit_;
}

auto RunnerInf::setFlagQuit(bool v) noexcept -> void{
    flagQuit_ = v;
}

FILEDISC_END