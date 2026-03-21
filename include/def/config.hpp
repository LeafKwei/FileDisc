#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "def/types.hpp"
FILEDISC_BEGIN

constexpr const char *MSGGLUE = "=>"; //提供给joinMessage使用，作为两段错误信息之间的分隔符
constexpr qint32 THREADCNT = 8;       //线程池数量上限为8

FILEDISC_END
#endif
