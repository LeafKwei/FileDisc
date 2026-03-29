#include <QApplication>
#include "def/config.hpp"
#include "jstp/JstpServer.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    JstpServer server;
    
    server.setPort(SERVER_PORT);
    if(server.listen()){
        qDebug() << "Error!!!";
    }
    
    return app.exec();
}