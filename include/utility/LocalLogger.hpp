#ifndef LOCALLOGGER_HPP
#define LOCALLOGGER_HPP

#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include "def/err.hpp"
#include "def/config.hpp"
FILEDISC_BEGIN

enum LogLevel{
    Info2Error,  //保存Info到Error级别的日志
    Debug2Error, //保存Debug到Error级别的日志
    Warn2Error,  //保存警告到Error级别的日志
    OnlyError    //仅保存Error级别的日志
};

/** 
 * 输出给定级别的日志信息到指定的文件中，日志文件由LocalLogger自动创建，此日志类确保不会抛出任何异常 
 * 日志示例：[2026-03-29 00:00:00] [Error] This is the error message.
 */
class LocalLogger{
public:
    explicit LocalLogger() noexcept;
    ~LocalLogger() noexcept;
    auto info(const QString &msg) noexcept -> void;
    auto debug(const QString &msg) noexcept -> void;
    auto warn(const QString &msg) noexcept -> void;
    auto error(const QString &msg) noexcept -> void;
    auto name() const noexcept -> QString;
    auto level() const noexcept -> LogLevel;
    auto setName(const QString &name) noexcept -> void;
    auto setLevel(LogLevel level) noexcept -> void;
    auto setBufferSize(quint32 size) noexcept -> void;
    auto setOutputPath(const QString &path) noexcept -> ErrBox; //设置Logger输出的文件路径，未设置时，所有日志都打印至终端
    auto restartLogger() noexcept -> void; //重启Logger以启用新的输出规则

private:
    auto resetAsTerminal() noexcept -> void;
    auto resetAsFile(const QString &path) noexcept -> void;
    
private:
    QMutex mutex_;
    QString path_;
    QString buffer_;
    quint32 size_;
    QString name_;
    LogLevel level_;
    QTextStream stream_;
};

FILEDISC_END
#endif
