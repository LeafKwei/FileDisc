#ifndef STATICKIT_HPP
#define STATICKIT_HPP

#include <QString>
#include "def/types.hpp"
FILEDISC_BEGIN

class StaticKit{
public:
    explicit StaticKit() =delete; //禁止构造对象
    static auto getLocalIpAddress() -> quint32;  //获取一个本地可用的IP地址
    static auto getRandomName(quint32 len) -> QString; //获取指定长度的随机名称
};

FILEDISC_END
#endif