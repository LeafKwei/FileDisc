#ifndef CNTLEDJOB_HPP
#define CNTLEDJOB_HPP

#include "thread/Job.hpp"
FILEDISC_BEGIN

class CntledJob : public Job{
public:
    CntledJob();
    auto id() const noexcept -> qint32 override;
    auto run() -> ErrCode override;
    auto moveMemberTo(QThread *thread) override;
    
private:
    auto cntl(RunnerInf &inf) -> void override;
};

FILEDISC_END
#endif
