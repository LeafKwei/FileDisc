#ifndef JSTPCLIENT_H
#define JSTPCLIENT_H

#include <QObject>
#include "def/types.hpp"
#include "jstp/HostStruct.hpp"
FILEDISC_BEGIN

class JstpClient : public QObject{
    Q_OBJECT
public:
    using HostVector = QVector<HostStruct>;
    
public:
    explicit JstpClient() =default;
    
private:
    
    
signals:
    
    
private slots:
    
};

FILEDISC_END
#endif
