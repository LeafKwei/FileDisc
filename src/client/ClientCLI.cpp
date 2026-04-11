#include <iostream>
#include <QApplication>
#include "def/config.hpp"
#include "utility/StaticKit.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
#if 1
    QApplication app(argc, argv);
    
    //=======================================
    for(int i = 0; i < 64; i++){
        qDebug() << "name = " << StaticKit::getRandomName(i);
    }
    
    //=======================================
    
    return app.exec();
#endif

}