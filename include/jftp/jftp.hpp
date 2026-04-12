#ifndef JFTP_H
#define JFTP_H

#include "def/types.hpp"
FILEDISC_BEGIN
/*///////// JFTP(Json and File Transfer Protocol)协议相关的声明与定义 /////////*/

/* 协议字段大小 */
//报文概览：[类型(64bit)] [数据长度(64bit)] [数据(n bit)]
constexpr quint32 JFTP_TYPE_SIZE = (sizeof(quint64));  //报文中的类型大小，类型高位4个字节为0，低位4个字节为类型的枚举值
constexpr quint32 JFTP_DATA_SIZE = (sizeof(quint64));  //报文中的数据大小
constexpr quint32 JFTP_HEAD_SIZE = (JFTP_TYPE_SIZE + JFTP_DATA_SIZE); //报文头部大小

/* 请求类型 */
enum class reqtype{
    GetHost = 0
};


/* 响应类型 */
enum class rsptype{
    GiveHost = 32
};

FILEDISC_END
#endif
