#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include "def/types.hpp"
#include "thread/ManagerInf.hpp"
#include "thread/Thread.hpp"
#include "thread/ThreadFunc.hpp"
#include "thread/JobQueue.hpp"
FILEDISC_BEGIN

class ThreadManager{
public:
    explicit ThreadManager();
    void createThreads(qint32 cnt);      //创建cnt数量的线程，仅可调用一次，重复调用会抛出异常
    bool hasFreeThread() const noexcept; //检查是否存在空闲的线程
    bool putJob(ThreadJobPtr job);       //添加任务到线程池，失败时返回false
    qint32 countJob() const noexcept;    //正在执行的任务数量
    qint32 countThread() const noexcept; //线程数量
    
private:
    ManagerInf inf_;
    JobQueue jobQueue_;
};

FILEDISC_END
#endif
