#ifndef JFTPREQUEST_HPP
#define JFTPREQUEST_HPP

#include "def/types.hpp"
#include "jftp/jftp.hpp"
FILEDISC_BEGIN
class JftpIO;

/*///////// JFTP协议的请求接口，所有请求都继承自此接口 /////////*/
class JftpRequest : public JftpIO{
public:
    virtual ~JftpRequest() noexcept =default;
    auto getType() const noexcept -> reqtype; //获取请求类型
    auto setType(reqtype type) const noexcept -> void; //设置请求类型
    auto readFrom(JftpIO &src) -> bool;  //从给定的JftpIO对象中读取数据并设置此对象
    auto writeTo(JftpIO &dst) -> bool;   //将此对象的数据写入到JftpIO对象
};

FILEDISC_END
#endif
