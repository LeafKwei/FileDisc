#include <QThread>
#include "utility/Defer.hpp"
#include "thread/Job.hpp"
#include "thread/JobQueue.hpp"
#include "thread/ThreadRunner.hpp"
FILEDISC_BEGIN

ThreadRunner::ThreadRunner(JobQueuePtr jobqptr)
    : inf_{}
    , jobqptr_(jobqptr)
{

}

void ThreadRunner::run(){
    /* 从任务队列中取出任务并执行 */
    while(true){
        /* 获取任务对象，同时设置延迟删除 */
        Job *job = jobqptr_ -> obtain();
        Defer deferDelete([&]() -> void{
            delete job;
        });
        
        /* 调用cntl函数对ThreadRunner进行控制 */
        job -> cntl(inf_);
        if(inf_.shouldQuit()){
            qDebug() << "Thread: " << QThread::currentThread() << "returned...";
            return;
        }
        
        /* 执行任务并发送信号 */
        emit to_jobStart(job -> id());
        auto err = job -> run();
        emit to_jobDone(job -> id(), err);
    }
}

FILEDISC_END