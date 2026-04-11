#ifndef JFTPRESPONSE_HPP
#define JFTPRESPONSE_HPP

#include "def/types.hpp"
#include "jftp/jftp.hpp"
#include "jftp/JftpIO.hpp"
FILEDISC_BEGIN

/*///////// JFTP协议的响应接口，所有响应都继承自此接口 /////////*/
class JftpResponse : public JftpIO{
public:
    virtual JftpResponse() noexcept =default;
    auto getType() const noexcept -> rsptype;
    auto setType(rsptype type) const noexcept -> void;
};

FILEDISC_END

#endif
