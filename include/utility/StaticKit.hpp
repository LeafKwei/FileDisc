#ifndef STATICKIT_HPP
#define STATICKIT_HPP

#include "def/types.hpp"
FILEDISC_BEGIN

class StaticKit{
public:
    explicit StaticKit() =delete;
    static auto getLocalIpAddress() -> quint32;
};

FILEDISC_END
#endif