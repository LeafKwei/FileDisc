#ifndef UDPWRAPPER_H
#define UDPWRAPPER_H

#include "jftp/io/JftpIO.hpp"
class QUdpSocket;
FILEDISC_BEGIN

/*///////// 对UDP套接字的包装 /////////*/
class UdpWrapper : public JftpIO{
public:
    explicit UdpWrapper(QUdpSocket *udp);
};

FILEDISC_END

#endif
