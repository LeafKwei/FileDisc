#include <QThread>
#include "utility/Defer.hpp"
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
        /* 获取任务对象，同时设置延迟删除 */
        Job *job = jobQueue_.obtain();
        Defer deferDelete([&]() -> void{
            job -> deleteLater();
        });
        
        /* 根据任务的cntl函数对ThreadRunner进行控制 */
        job -> cntl(inf_);
        if(inf_.shouldQuit()){
            return;
        }
        
        /* 执行任务并发送信号 */
        emit to_jobStart(job -> id());
        job -> moveMemberTo(QThread::currentThread());
        auto err = job -> run();
        emit to_jobDone(job -> id(), err);
    }
}

FILEDISC_END