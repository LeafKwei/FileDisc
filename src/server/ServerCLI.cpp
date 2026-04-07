#include <iostream>
#include <QApplication>
#include "jstp/JstpServer.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
#if 1
    QApplication app(argc, argv);
    
    //=======================================
    JstpServer server;
    auto err = server.initServer();
    if(err){
        qDebug() << err.errmsg();
        return -1;
    }
    //=======================================
    
    return app.exec();
#endif

}