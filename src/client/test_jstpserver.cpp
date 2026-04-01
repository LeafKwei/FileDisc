#include <iostream>
#include <QApplication>
#include <QFile>
#include "jstp/JstpClient.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
#if 1
    QApplication app(argc, argv);
    
    //=======================================
    JstpClient client;
    if(client.requestHost().err){
        qDebug() << "哦豁！";
    }
    else{
        qDebug() << "YES.";
    }
    
    //=======================================
    
    return app.exec();
#endif
}