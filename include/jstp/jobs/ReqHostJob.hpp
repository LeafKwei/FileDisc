#ifndef REQHOSTJOB_HPP
#define REQHOSTJOB_HPP

#include "jstp/JstpEmiter.hpp"
#include "jstp/jobs/JstpJob.hpp"
FILEDISC_BEGIN

class ReqHostJob : public JstpJob{
public:
    explicit ReqHostJob(qint32 id);
    auto run() noexcept -> ErrCode override; 
};

FILEDISC_END
#endif
