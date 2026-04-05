#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "def/types.hpp"
FILEDISC_BEGIN
/*///////// 定义各种常量配置信息 /////////*/

constexpr qsizetype MAX_JOB = 64;    //JobQueue允许缓存的最大任务数
constexpr qsizetype MAX_THRAED = 8;  //ThreadManager允许创建的最大线程数
constexpr quint32 LOGBUFFER_SIZE = 65535; //最大日志缓存长度
constexpr quint16 SERVER_PORT = 7981; //Server监听的端口
constexpr quint16 CLIENT_PORT = 7982; //Client监听的端口

FILEDISC_END
#endif
