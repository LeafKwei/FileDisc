#include "thread/Job.hpp"
#include "thread/JobQueue.hpp"
#include "thread/ThreadRunner.hpp"
FILEDISC_BEGIN

ThreadRunner::ThreadRunner(JobQueue &jobQueue) : jobQueue_(jobQueue)
{

}

auto ThreadRunner::run() -> void{
    /* 从任务队列中取出任务并执行 */
    while(true){
        JobPtr job = jobQueue_.obtain();
        if(job.isNull()) qDebug() << "Fuckkkkk2!";
        emit to_jobstart(job -> id());
        auto result = job -> run();
        emit to_jobdone(job -> id(), result);
    }
}

FILEDISC_END