#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "def/types.hpp"
FILEDISC_BEGIN
/*///////// 定义各种常量配置信息 /////////*/

constexpr const char *MSG_GLUE = "=>"; //提供给joinMessage使用，作为两段错误信息之间的分隔符
constexpr qint32 MIN_INFO_SIZE = sizeof("JSTP") + sizeof(qint8) + sizeof(qint32); //进行TCP通信时，必须读到这么多字节后才开始解析
constexpr qint32 MAX_JOB = 64;    //JobQueue允许缓存的最大任务数
constexpr qint32 MAX_THRAED = 8;  //ThreadManager允许创建的最大线程数
constexpr quint32 LOGBUFFER_SIZE = 65535; //最大日志缓存长度
constexpr quint16 SERVER_PORT = 7981; //Server监听的端口

FILEDISC_END
#endif
