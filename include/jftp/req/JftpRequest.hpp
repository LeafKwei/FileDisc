#ifndef JFTPREQUEST_HPP
#define JFTPREQUEST_HPP

#include "def/types.hpp"
#include "jftp/jftp.hpp"
FILEDISC_BEGIN

class JftpRequest{
public:
    auto type() const noexcept -> reqtype;
};

FILEDISC_END
#endif
