#include <iostream>
#include <QApplication>
#include <QFile>
#include "jstp/JstpPayload.hpp"
using namespace fidi;

int main(int argc, char *argv[]){
#if 0
    QApplication app(argc, argv);

    
    
    return app.exec();
#endif



    QString json = R"(
        {
            "type" : "0",
            "long_key" : "abc123",
            "short_key" : "abc",
            "begin_path" : "/a/b/c",
            "target" : "hello.txt",
            "target_size" : "189929",
            "host" : {
                "ip" : "192.168.8.6",
                "port" : "8980"
            },
            
            "files" : [
                {"name" : "a.txt", "size" : "199"},
                {"name" : "b.txt", "size" : "200"},
                {"name" : "c.txt", "size" : "201"}
            ],
            
            "dirs" : [
                {"name" : "a"},
                {"name" : "b"},
                {"name" : "c"}
            ]
        }
    )";
    
    JstpPayload payload;
    if(ErrBox err = payload.fromJson(json); err){
        qDebug() << "Error: " << err.errmsg();
    }
    
    // qDebug() << payload.getPair(JSTP_TYPE);
    // qDebug() << payload.getPair(JSTP_BEGIN);
    // qDebug() << payload.getHostField().ip;
    std::cout << payload.toString().toStdString() << std::endl;
    
    
    return 0;
}