#ifndef ERR_HPP
#define ERR_HPP

#include <QGlobal.h>
#include <QString>
#include "def/version.hpp"
FILEDISC_BEGIN
/*///////// 定义错误处理相关的数据结构 /////////*/

using ErrStr = QString;

/* 将程序中的错误枚举为错误码 */
enum class ErrCode{
    OK = 0,
    Busy,
    JobInit,
    TCPListen,
    UDPBind,
    BadJson,
    BroCasSend,
};

/* 错误信息的封装类(在mixed.cpp中实现) */
class ErrBox{
public:
    explicit ErrBox(ErrCode code=ErrCode::OK);
    explicit ErrBox(ErrCode code, const ErrStr &msg);
    auto errcode() const noexcept -> ErrCode;
    auto errmsg() const noexcept -> ErrStr;
    auto hasError() const noexcept -> bool;
    operator bool() const noexcept;
    
private:
    ErrCode code_;
    ErrStr  msg_;
};

/* 为ErrBox增加一个OkBox的别名。在无错误时使用OkBox返回可以让语义更清晰 */
using OkBox = ErrBox;

FILEDISC_END
#endif
