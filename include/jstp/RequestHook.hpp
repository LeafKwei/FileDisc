#ifndef REQUESTHOOK_HPP
#define REQUESTHOOK_HPP

#include <functional>
#include "def/types.hpp"
#include "jstp/JstpPayload.hpp"
FILEDISC_BEGIN

/*///////// 对JSTP请求进行hook的函数接口 /////////*/
using RequestHook = std::function<bool(JstpRequest &req)>;

FILEDISC_END
#endif
