#ifndef TYPES_HPP
#define TYPES_HPP

#include <QtGlobal>
#include <QSharedPointer>
#include "def/err.hpp"
FILEDISC_BEGIN

/* 使函数可以同时返回返回值和错误码 */
template<typename V, typename E=ErrCode>
struct Result{
    V val;
    E err;
};

FILEDISC_END
#endif
