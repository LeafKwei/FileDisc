#ifndef TCPWRAPPER_HPP
#define TCPWRAPPER_HPP

#include "jftp/io/JftpIO.hpp"
class QTcpSocket;
FILEDISC_BEGIN

/*///////// 对TCP套接字的包装 /////////*/
class TcpWrapper : public JftpIO{
public:
    explicit TcpWrapper(QTcpSocket *tcp);
};

FILEDISC_END
#endif
