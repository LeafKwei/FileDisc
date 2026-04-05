#ifndef SERVER_HOLDER_HPP
#define SERVER_HOLDER_HPP

#include <QThread>
#include "def/config.hpp"
#include "thread/Job.hpp"
#include "thread/ThreadManager.hpp"

using namespace fidi;

class Emiter : public QObject{
    Q_OBJECT
signals:
    void to_fuck(qint32 );
        
public:
    void call_fuck(qint32 i){
        emit to_fuck(i);
    }
};

class MyJob : public Job{
public:
    MyJob(qint32 jobid): id_(jobid){
    
    }
    
    ~MyJob(){
        qDebug() << "Delete MyJob: " << id_;
    }
    
    auto id() const noexcept -> qint32 override{
        return id_;
    }
    
    auto emiter() -> Emiter*{
        return &emiter_;
    }
    
    auto run() noexcept -> ErrCode override{
        //qDebug() << "job: " << id_ << " ---> start: " << QThread::currentThread();
        QThread::msleep(5000);
        emiter_.call_fuck(id_);
        //qDebug() << "job: " << id_ << " ---> done: " << QThread::currentThread();
        return ErrCode::OK;
    }
    
private:
    Emiter emiter_;
    qint32 id_;
};

class Work : public QObject{
    Q_OBJECT
public:
    Work() : manager(MAX_THRAED, MAX_JOB){
    
    }
    
public slots:
    void run(){
        for(int i = 0; i < 10; i++){
            MyJob *job = new MyJob(i);
            connect(job -> emiter(), &Emiter::to_fuck, this, &Work::at_jobfuck);
            manager.sendToQueue(job);
            QThread::msleep(1000);
        }
    }
    
    void at_jobfuck(qint32 i){
        qDebug() << "Get the fuck qint32: " << i; 
    }
    
private:
    ThreadManager manager;
};

class Work2 : public QObject{
    Q_OBJECT
public:
    Work2(){
    
    }
    
public slots:
    void run(){
        ThreadManager manager(MAX_THRAED, MAX_JOB);
        
        for(int i = 0; i < 10; i++){
            MyJob *job = new MyJob(i);
            connect(job -> emiter(), &Emiter::to_fuck, this, &Work2::at_jobfuck);
            manager.sendToQueue(job);
            QThread::msleep(1000);
        }
    }
    
    void at_jobfuck(qint32 i){
        qDebug() << "Get the fuck2 qint32: " << i; 
    } 
};

#endif // SERVER_HOLDER_HPP
