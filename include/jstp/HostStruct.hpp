#ifndef HOSTSTRUCT_HPP
#define HOSTSTRUCT_HPP

#include <QHostAddress>
#include "def/types.hpp"
FILEDISC_BEGIN

class HostStruct{
public:
    using RoQHostAddress = const QHostAddress&;

public:
    explicit HostSruct(QHostAddress addr, quint16 port=0);
    explicit HostSruct(qint32 addr, quint16 port=0);
    RoQHostAddress ip() const noexcept;
    quint16 port() const noexcept;
private:
    QHostAddress ip_;
    quint16      port_;
};

FILEDISC_END
#endif
