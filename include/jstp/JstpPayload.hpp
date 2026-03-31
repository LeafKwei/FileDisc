#ifndef JSTPPAYLOAD_HPP
#define JSTPPAYLOAD_HPP

#include <QHash>
#include <QVector>
#include <QJsonObject>
#include "def/types.hpp"
#include "jstp/jstp.hpp"
FILEDISC_BEGIN

/*///////// 对JSTP协议JSON部分的封装，可转换/被转换为JSON /////////*/
class JstpPayload{
public:
    constexpr static qint32 FLAG_HOST = 1;  //具有host字段
    constexpr static qint32 FLAG_FILES = 1 << 1; //具有files字段
    constexpr static qint32 FLAG_DIRS = 1 << 2;  //具有dirs字段
    
public:
    explicit JstpPayload();
    auto setPair(const QString &key, const QString &value) -> void; //为给定的键设置对应的值
    auto setHostField(const JstpHostField &host) -> void; //添加主机信息
    auto pushFileField(const JstpFileField &file) -> void; //添加文件信息
    auto pushDirField(const JstpDirField &dir) -> void; //添加目录信息
    auto getPair(const QString &key) -> QString;  //获取键对应的值
    auto getHostField() -> JstpHostField; //获取主机字段
    auto getFileField() -> QVector<JstpFileField>; //获取文件字段组成的Vector
    auto getDirField() -> QVector<JstpDirField>;   //获取目录字段组成的Vector
    auto fromJson(const QString &json) -> ErrBox;  //从json字符串中解析出请求信息
    auto fromJson(const QByteArray &json) -> ErrBox; //从json字节数组中解析出请求信息
    auto hasFlag(qint32 flag) -> bool; //检查是否含有指定的flag
    auto setFlag(qint32 flag) -> void; //设置flag
    auto unsetFlag(qint32 flag) -> void; //取消flag
    auto toString() -> QString;  //转换为JSON字符串
    auto toByteArray() -> QByteArray; //转换为字节数组
    
private:
    auto takeHost(QJsonObject &obj) -> void; //注意，take*函数在取出元素的同时会将该元素置空
    auto takeFiles(QJsonObject &obj) -> void;
    auto takeDirs(QJsonObject &obj) -> void;
    auto takePairs(QJsonObject &obj) -> void;
    auto fillPairs(QJsonObject &obj) -> void;
    auto fillHost(QJsonObject &obj) -> void;
    auto fillFiles(QJsonObject &obj) -> void;
    auto fillDirs(QJsonObject &obj) -> void;
    
private:
    qint32 flag_;
    JstpHostField host_;
    QHash<QString, QString> pairs_;
    QVector<JstpFileField> files_;
    QVector<JstpDirField> dirs_;
};

FILEDISC_END
#endif
