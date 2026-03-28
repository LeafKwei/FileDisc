#ifndef TEST_MAIN_H
#define TEST_MAIN_H
#include <QObject>
#include <QThread>
#include "thread/ThreadManager.hpp"
using namespace fidi;

class TestJob : public Job{
public:
    static qint32 idcnt;
    
public:
    TestJob(){ id_ = idcnt++; qDebug() << id_ << " Job created..."; }
    ~TestJob() noexcept override{ qDebug() << id_ << " Job deleted..."; }

    auto id() const noexcept -> qint32{
        qDebug() << id_ << " id was called.";
        return 114514;
    }
    
    auto run() -> void{
        QThread::msleep(5000);
        qDebug() << id_ << " run was called.";
    }
    
private:
    qint32 id_;
};

class Worker : public QObject{
    Q_OBJECT
public:
    Worker(ThreadManager &mngr) : mngr_(mngr){
    
    }
    
    void run(){
        QThread::msleep(1000);
        for(int i = 0; i < 20; i++){
            auto job = new TestJob;
            QThread::msleep(500);
            mngr_.sendToQueue(job);
        }
    }
    
private:
    ThreadManager &mngr_;
};

class Fuck : public QObject{
    Q_OBJECT
public:
    Fuck() : manager(10){
    
    }

    void testThread(){
        qDebug() << "test-tid: " <<QThread::currentThreadId();
        auto creator = new QThread;
        auto worker = new Worker(manager);
        worker -> moveToThread(creator); //Fuck you!!!!
        connect(creator, &QThread::started, worker, [worker]() -> void {
            qDebug() << "run-tid: " <<QThread::currentThreadId();
            worker -> run();
        });
        connect(creator, SIGNAL(finished()), creator, SLOT(deleteLater()));
        connect(creator, SIGNAL(finished()), worker, SLOT(deleteLater()));
        creator -> start();
    }

private:
    ThreadManager manager;
};

// class Work : public QObject{
//     Q_OBJECT
// signals:
// 	void to_heartbeat(qint32 i);
    
// public slots:
// 	void run(){
// 		for(int i = 0; i < 1000; i++){
// 			QThread::msleep(500);
// 			emit to_heartbeat(i);
// 		}
// 	}
// };

// class Listener : public QObject{
// 	Q_OBJECT	
// public slots:
//     void from_heartbeat(qint32 i){
//         qDebug() << "receive heartbeat: " << i << ", heart-tid: " << QThread::currentThreadId();
//     }
// };

#endif
