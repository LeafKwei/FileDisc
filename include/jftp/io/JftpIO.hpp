#ifndef JFTPIO_HPP
#define JFTPIO_HPP

#include <stdint.h>
#include "def/err.hpp"
#include "def/types.hpp"
FILEDISC_BEGIN

/*///////// JFTP协议统一IO接口 /////////*/
class JftpIO{
public:
    using RoErrBox = const ErrBox&;
    
public:
    virtual ~JftpIO() noexcept =default;
    virtual auto error() const noexcept -> RoErrBox; //获取最近一次的IO错误信息
    virtual auto readable() const noexcept -> bool;  //是否可读
    virtual auto writeable() const noexcept -> bool; //是否可写
    virtual auto read(char *buffer, uint64_t size) -> uint64_t;        //读取指定数量的字节到buffer，返回实际读取的字节数量
    virtual auto write(const char *buffer, uint64_t size) -> uint64_t; //写入buffer中指定数量的字节，返回实际写入的字节数量
};

FILEDISC_END
#endif
