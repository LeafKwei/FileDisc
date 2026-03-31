#ifndef JSTP_HPP
#define JSTP_HPP

#include <QString>
#include "def/types.hpp"
FILEDISC_BEGIN
/*///////// 定义请求类型 /////////*/
enum class ReqType{
    Test = 0,     //仅测试数据通路，服务端会忽略此请求
    HostInfo, //请求主机信息
    Auth,     //请求验证
    DirList,  //请求目录列表
    Download  //下载指定文件
};

/*///////// 定义响应类型 /////////*/
enum class RspType{
    Test = 300,   //仅测试数据通路，客户端会忽略此响应
    Auth,   //此报文为服务端为此主机生成的密钥
    Done,   //服务端成功响应并已处理请求
    Invalid //请求有误
};

/*///////// 定义协议字段常量 /////////*/
constexpr const char *JSTP_TYPE = "type";
constexpr const char *JSTP_LKEY = "long_key";
constexpr const char *JSTP_SKEY = "short_key";
constexpr const char *JSTP_BEGIN = "begin_path";
constexpr const char *JSTP_TARGET = "target";
constexpr const char *JSTP_TARGETSIZE = "target_size";
constexpr const char *JSTP_HOST = "host";
constexpr const char *JSTP_HOST_IP = "ip";
constexpr const char *JSTP_HOST_PORT = "port";
constexpr const char *JSTP_FILES = "files";
constexpr const char *JSTP_FILES_NAME = "name";
constexpr const char *JSTP_FILES_SIZE = "size";
constexpr const char *JSTP_DIRS = "dirs";
constexpr const char *JSTP_DIRS_NAME = "name";

/*///////// 定义简单结构 /////////*/
struct JstpHostField{
    quint32 ip;    //用户需要确保ip和port为网络字节序
    quint16 port;
};

struct JstpFileField{
    QString name;
    qint64 size;
};

struct JstpDirField{
    QString name;
};

FILEDISC_END
#endif
