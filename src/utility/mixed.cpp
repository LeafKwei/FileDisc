#include "def/err.hpp"
#include "def/types.hpp"
#include "utility/Defer.hpp"
FILEDISC_BEGIN
/*///////// 此源文件用于收集各种简短工具类的函数实现 /////////*/
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

/* Defer */
Defer::Defer(DeferFunc df)
    : df_(df)
{

}

Defer::~Defer() noexcept{
    try{
        if(df_){
            df_();
        }
    }
    catch(...){
        qCritical() << "Critical error in Defer.~Defer(): You SHOULD NOT throw any exceptions.";
    }
}

FILEDISC_END