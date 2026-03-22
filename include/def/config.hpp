#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "def/types.hpp"
FILEDISC_BEGIN

constexpr const char *MSG_GLUE = "=>"; //提供给joinMessage使用，作为两段错误信息之间的分隔符
constexpr qint32 MIN_INFO_SIZE = sizeof("JSTP") + sizeof(qint8) + sizeof(qint32); //进行TCP通信时，必须读到这么多字节后才开始解析
constexpr qint32 MAX_THREAD = 8;       //线程池数量上限为8
constexpr qint32 MAX_JOB = 128;        //最大任务数量

FILEDISC_END
#endif
