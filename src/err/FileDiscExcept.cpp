#include "err/FileDiscExcept.hpp"
FILEDISC_BEGIN

static QString joinMessage(const QString &newmsg, const QString &lastmsg, const QString &glue){
    return (newmsg.isEmpty()) ? (lastmsg) : (newmsg + glue + lastmsg);
}

FileDiscExcept::FileDiscExcept(const QString &msg, const QString &loc) 
    : msg_(msg)
    , loc_(loc)
{
    
}

QString FileDiscExcept::what() const noexcept{
    return msg_;
}

QString FileDiscExcept::where() const noexcept{
    return loc_;
}


FILEDISC_END