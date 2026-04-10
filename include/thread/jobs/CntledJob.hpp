#ifndef CNTLEDJOB_HPP
#define CNTLEDJOB_HPP

#include "thread/Job.hpp"
FILEDISC_BEGIN

/*///////// 控制型任务，不负责实际的作业，专门实现cntl函数以控制ThreadRunner的属性信息 /////////*/
class CntledJob : public Job{
public:
    CntledJob();
    auto id() const noexcept -> idtype override;
    auto run() noexcept -> ErrCode override;
    
private:
    auto cntl(RunnerInf &inf) -> void override;
};

FILEDISC_END
#endif
