#ifndef REQFILEJOB_HPP
#define REQFILEJOB_HPP

#include "jstp/JstpEmiter.hpp"
#include "jstp/jobs/JstpJob.hpp"
FILEDISC_BEGIN

class ReqFileJob : public JstpJob{
public:
    explicit ReqFileJob(qint32 id, JstpHostField server);
    auto run() noexcept -> ErrCode override;
    
private:
    JstpHostField server_;
};


#endif
FILEDISC_END
