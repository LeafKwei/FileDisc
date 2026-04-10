#ifndef JFTPRESPONSE_HPP
#define JFTPRESPONSE_HPP

#include "def/types.hpp"
#include "jftp/jftp.hpp"
FILEDISC_BEGIN

class JftpResponse{
public:
    auto type() const noexcept -> rsptype;
};

FILEDISC_END

#endif
