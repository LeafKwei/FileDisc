#include "thread/Job.hpp"
#include "thread/JobQueue.hpp"
#include "thread/ThreadRunner.hpp"
FILEDISC_BEGIN

ThreadRunner::ThreadRunner(JobQueue &jobQueue) : jobQueue_(jobQueue)
{
    qDebug() << "thread: " << reinterpret_cast<quint64>(this) << "created...";
}

auto ThreadRunner::run() -> void{
    /* 从任务队列中取出任务并执行 */
    while(true){
        /* 获取任务对象，同时连接删除函数以便自动释放 */
        Job *job = jobQueue_.obtain();
        
        /* 执行任务并发送信号 */
        emit to_jobstart();
        job -> run();
        emit to_jobdone();
        
        /* 删除任务 */
        job -> deleteLater();
    }
}

FILEDISC_END