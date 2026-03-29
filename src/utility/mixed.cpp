#include "def/err.hpp"
FILEDISC_BEGIN
/* 此源文件用于收集各种简短工具类的函数实现 */
/* ErrBox */
ErrBox::ErrBox(ErrCode code, ErrStr msg)
    : code_(code)
    , msg_(msg)
{

}

auto ErrBox::errcode() const noexcept -> ErrCode{
    return code_;
}

auto ErrBox::errmsg() const noexcept -> ErrStr{
    return msg_;
}

auto ErrBox::hasError() const noexcept -> bool{
    return code_ != ErrCode::OK;
}

ErrBox::operator bool() const noexcept{
    return hasError();
}

FILEDISC_END