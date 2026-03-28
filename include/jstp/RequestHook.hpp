#ifndef REQUESTHOOK_H
#define REQUESTHOOK_H

#include <functional>
#include "def/types.hpp"
#include "jstp/JstpRequest.hpp"
FILEDISC_BEGIN

using RequestHook = std::function<bool(JstpRequest &req)>;

FILEDISC_END
#endif
