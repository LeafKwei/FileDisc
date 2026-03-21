#ifndef ERR_HPP
#define ERR_HPP

#include <QGlobal.h>
#include <QString>
#include "def/version.hpp"
FILEDISC_BEGIN

/* 使用ErrStruct保存错误码和字面量形式的错误信息 */
enum class ErrCode{
    OK = 0
};

struct ErrStruct{
    ErrCode err;
    const char *msg;
};


FILEDISC_END
#endif
