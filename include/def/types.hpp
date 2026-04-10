#ifndef TYPES_HPP
#define TYPES_HPP

#include <QtGlobal>
#include <QDebug>
#include "def/err.hpp"
FILEDISC_BEGIN
/*///////// 定义通用类型 /////////*/

/* 使函数可以同时返回返回值和错误信息 */
template<typename V, typename E=ErrBox>
struct Result{
    V val;
    E err;
};

using idtype = qint32;  //用于各种id标识的类型

FILEDISC_END
#endif
