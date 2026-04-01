#ifndef REQUESHOSTJOB_HPP
#define REQUESHOSTJOB_HPP

#include <QUdpSocket>
#include "jstp/jobs/JstpJob.hpp"
FILEDISC_BEGIN

class RequesHostJob : public JstpJob{
    Q_OBJECT
public:
    explicit RequesHostJob(qint32 id, QUdpSocket &broadsock);
    auto run() -> void override;
    
private:
    QUdpSocket &broadsock_;

signals:
    void to_requestHostJobDone(qint32 id, ErrCode err);
};

FILEDISC_END
#endif
