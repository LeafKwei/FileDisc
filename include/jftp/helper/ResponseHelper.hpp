#ifndef RESPONSEHELPER_HPP
#define RESPONSEHELPER_HPP

#include "def/types.hpp"
FILEDISC_BEGIN
class JftpIO;
class JftpResponse;

class ResponseHelper{
public:
    auto getResponseFrom(JftpIO &src) -> Result<JftpResponse*>;
};

FILEDISC_END
#endif
