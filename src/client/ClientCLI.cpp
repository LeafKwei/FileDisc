#include <iostream>
#include <QApplication>
#include "def/config.hpp"
#include "jstp/JstpClient.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
#if 1
    QApplication app(argc, argv);
    
    //=======================================
    JstpClient client;
    auto err = client.initClient();
    if(err){
        qDebug() << err.errmsg();
        return -1;
    }
    
    auto result = client.requestHost();
    qDebug() << result.val;
    if(result.err){
        qDebug() << result.err.errmsg();
        return -1;
    }
    
    JstpHostField server{
        "",
        QHostAddress("127.0.0.1").toIPv4Address(),
        SERVER_PORT
    };
    
    result = client.requestFile(server, "", "");
    if(result.err){
        qDebug() << result.err.errmsg();
    }
    
    //=======================================
    
    return app.exec();
#endif

}