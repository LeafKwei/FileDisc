#ifndef JFTPIO_HPP
#define JFTPIO_HPP

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
    virtual auto readFrom(void *src) -> bool; //从指定的源对象中读取数据到当前对象
    virtual auto writeTo(void *dst) -> bool;  //将当前对象的内容写入到指定的目的对象dst中
};

FILEDISC_END
#endif
