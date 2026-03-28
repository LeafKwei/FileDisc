#include <QApplication>
#include <QDebug>
#include "client/test_main.hpp"

qint32 TestJob::idcnt = 0;

// int main(int argc, char *argv[]){
// 	QApplication app(argc, argv);
// 	QThread thread;
// 	Listener listener;
// 	Work work;
	
// 	//work.moveToThread(&thread);
// 	qDebug() << "main-tid: " << QThread::currentThreadId();
// 	QObject::connect(&thread, &QThread::started, &work, [&]() -> void{
//         qDebug() << "work-tid: " << QThread::currentThreadId();
//         work.run();
// 	}, Qt::AutoConnection);
//     QObject::connect(&work, SIGNAL(to_heartbeat(qint32)), &listener, SLOT(from_heartbeat(qint32)), Qt::QueuedConnection);
//     thread.start();    
    
//     return app.exec();
// }


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Fuck fuck;
    fuck.testThread();
    
    qDebug() << "Ready to run exec...";
    return a.exec();
}