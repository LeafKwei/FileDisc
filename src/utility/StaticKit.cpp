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

FILEDISC_END