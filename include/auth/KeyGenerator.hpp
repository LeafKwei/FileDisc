#ifndef KEYGENERATOR_HPP
#define KEYGENERATOR_HPP

#include <QString>
#include "def/version.hpp"
FILEDISC_BEGIN

class KeyGenerator{
public:
    explicit KeyGenerator(qint32 length); //创建一个生成length长度密钥的生成器
    auto generateFrom(const QString &str) -> QString;  //基于给定的字符串生成密钥
};

FILEDISC_END
#endif
