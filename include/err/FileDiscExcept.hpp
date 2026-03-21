#ifndef FILEDISCEXCEPT_HPP
#define FILEDISCEXCEPT_HPP

#include <QString>
#include "def/types.hpp"
FILEDISC_BEGIN

class FileDiscExcept{
public:
    static QString joinMessage(
        const QString &newmsg, 
        const QString &lastmsg, 
        const QString &glue);

public:
    explicit FileDiscExcept(const QString &msg, const QString &loc);
    QString what() const noexcept;
    QString where() const noexcept;

private:
    QString msg_;
    QString loc_;
};

FILEDISC_END
#endif
