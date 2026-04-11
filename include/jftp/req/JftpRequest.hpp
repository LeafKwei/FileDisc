#ifndef JFTPREQUEST_HPP
#define JFTPREQUEST_HPP

#include "def/types.hpp"
#include "jftp/jftp.hpp"
#include "jftp/JftpIO.hpp"
FILEDISC_BEGIN

/*///////// JFTP协议的请求接口，所有请求都继承自此接口 /////////*/
class JftpRequest : public JftpIO{
public:
    virtual ~JftpRequest() noexcept =default;
    auto getType() const noexcept -> reqtype;
    auto setType(reqtype type) const noexcept -> void;
};

FILEDISC_END
#endif
