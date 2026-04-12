#ifndef REQUESTHELPER_HPP
#define REQUESTHELPER_HPP

#include "def/types.hpp"
FILEDISC_BEGIN
class JftpIO;
class JftpRequest;

class RequestHelper{
public:
    auto getRequestFrom(JftpIO &src) -> Result<JftpRequest*>;
};

FILEDISC_END
#endif
