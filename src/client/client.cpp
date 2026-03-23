#include <QObject>
#include <QApplication>
#include "thread/ThreadManager.hpp"

using namespace fidi;

class TestJob : public Job{
public:
    TestJob(){ qDebug() << "Job created..."; }
    ~TestJob(){ qDebug() << "Job deleted..."; }

    auto id() const noexcept -> qint32{
        qDebug() << "id was called.";
        return 114514;
    }
    
    auto run() -> Result<QVariant>{
        qDebug() << "run was called.";
        return {1919810, ErrCode::OK};
    }
};

class Fuck{
public:
    Fuck() : manager(10){
    
    }

    void testThread(){
        auto job = new TestJob;
        manager.sendToQueue(JobPtr(job));
    }
    
private:
    ThreadManager manager;
};

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Fuck fuck;
    fuck.testThread();
    return a.exec();
}