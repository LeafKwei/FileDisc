#include <QRandomGenerator>
#include <QNetworkInterface>
#include <QList>
#include <QHostAddress>
#include "utility/StaticKit.hpp"
FILEDISC_BEGIN

auto StaticKit::getLocalIpAddress() -> quint32{
    auto interfs = QNetworkInterface::allInterfaces();
    foreach (const QNetworkInterface &interf, interfs) {
        /* 过滤未启用的网卡 */
        if(!(interf.flags() & QNetworkInterface::IsUp)){
            continue;
        }
        
        /* 找到第一个非回环IP地址 */
        auto addrs = interf.allAddresses();
        foreach (const QHostAddress &addr, addrs) {
            if(addr.protocol() == QAbstractSocket::IPv4Protocol && !addr.isLoopback()){
                return addr.toIPv4Address();
            }
        }
    }
    
    return 0;
}

auto StaticKit::getRandomName(quint32 len) -> QString{
    static QChar arr[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        '_'
    };
    
    auto rand = QRandomGenerator::global();
    QString name;
    
    
    for(auto idx = 0; idx < len; idx++){
        auto ch = arr[(rand -> bounded((qint32)0, (qint32)((sizeof(arr) / sizeof(QChar)))))];
        name.append(ch);
    }
    
    return name;
}

FILEDISC_END