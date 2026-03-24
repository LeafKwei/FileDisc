#include <QApplication>
#include <QDebug>
#include "client/test_main.hpp"

qint32 TestJob::idcnt = 0;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Fuck fuck;
    fuck.testThread();
    
    qDebug() << "Ready to run exec...";
    return a.exec();
}