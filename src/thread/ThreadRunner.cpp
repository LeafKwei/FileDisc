#include <QThread>
#include "thread/Job.hpp"
#include "thread/JobQueue.hpp"
#include "thread/ThreadRunner.hpp"
FILEDISC_BEGIN

ThreadRunner::ThreadRunner(JobQueue &jobQueue) 
    : jobQueue_(jobQueue)
{

}

void ThreadRunner::run(){
    /* 从任务队列中取出任务并执行 */
    while(true){
        /* 获取任务对象 */
        Job *job = jobQueue_.obtain();
        
        /* 执行任务并发送信号 */
        emit to_jobStart(job -> id());
        job -> moveMemberTo(QThread::currentThread());
        auto err = job -> run();
        emit to_jobDone(job -> id(), err);
        
        /* 删除任务 */
        job -> deleteLater();
    }
}

FILEDISC_END