#include "thread/jobs/CntledJob.hpp"
FILEDISC_BEGIN

CntledJob::CntledJob()
{

}

auto CntledJob::id() const noexcept -> qint32{
    /* 空实现 */
    return 0;
}

auto CntledJob::run() noexcept -> ErrCode{
    /* 空实现 */
    return ErrCode::Ok;
}

auto CntledJob::cntl(RunnerInf &inf) -> void{
    inf.setFlagQuit(true);
}

FILEDISC_END