#include <iostream>
#include <QApplication>
#include <QFile>
#include "server/server_holder.hpp"
#include "thread/ThreadManager.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
#if 0
    QApplication app(argc, argv);
    
    //=======================================
    qDebug() << "Test start.";
    Work work;
    QThread thread;
    work.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &work, &Work::run);
    thread.start();
    qDebug() << "Test end.";

    //=======================================
    
    return app.exec();
#endif

#if 1
    QApplication app(argc, argv);
    
    //=======================================
    qDebug() << "Test start.";
    Work2 work;
    QThread thread;
    work.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &work, &Work2::run);
    thread.start();
    qDebug() << "Test end.";

    //=======================================
    
    return app.exec();
#endif
}