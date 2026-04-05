#include "def/err.hpp"
#include "def/types.hpp"
#include "utility/Defer.hpp"
FILEDISC_BEGIN
/* ErrBox */
ErrBox::ErrBox(ErrCode code)
    : code_(code)
    , msg_("OK.")
{

}

ErrBox::ErrBox(ErrCode code, const ErrStr &msg)
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