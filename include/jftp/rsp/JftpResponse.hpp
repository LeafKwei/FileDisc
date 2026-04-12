#ifndef JFTPRESPONSE_HPP
#define JFTPRESPONSE_HPP

#include "def/types.hpp"
#include "jftp/jftp.hpp"
FILEDISC_BEGIN
class JftpIO;

/*///////// JFTP协议的响应接口，所有响应都继承自此接口 /////////*/
class JftpResponse : public JftpIO{
public:
    virtual JftpResponse() noexcept =default;
    auto getType() const noexcept -> rsptype;    //获取响应类型
    auto setType(rsptype type) const noexcept -> void; //设置响应类型
    auto readFrom(JftpIO &src) -> bool;  //从JftpIO对象中读取数据并设置此对象
    auto writeTo(JftpIO &dst) -> bool;   //将此对象的数据写入到JftpIO对象
};

FILEDISC_END

#endif
