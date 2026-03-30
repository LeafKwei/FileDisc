#ifndef REQ_HPP
#define REQ_HPP

#include "def/version.hpp"
FILEDISC_BEGIN
/*///////// 定义请求类型 /////////*/
enum class ReqType{
    Test,     //仅测试数据通路，什么动作也不做
    HostInfo, //请求主机信息
    DirList,  //请求目录列表
    Download  //下载指定文件
};

FILEDISC_END
#endif
