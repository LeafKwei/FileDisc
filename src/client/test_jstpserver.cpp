#include <iostream>
#include <QApplication>
#include "jstp/JstpClient.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
#if 1
    QApplication app(argc, argv);
    
    //=======================================
    JstpClient client;
    auto result = client.requestHost();
    qDebug() << result.val;
    if(result.err){
        qDebug() << result.err.errmsg();
    }
    //=======================================
    
    return app.exec();
#endif

}