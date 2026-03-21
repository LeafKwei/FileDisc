#ifndef THREADFUNC_H
#define THREADFUNC_H

#include <functional>
#include "def/types.hpp"
FILEDISC_BEGIN

class JobQueue;
class ManagerInf;
using ThreadFunc = std::function<void(JobQueue &jobQueue, ManagerInf &inf)>;

FILEDISC_END
#endif
