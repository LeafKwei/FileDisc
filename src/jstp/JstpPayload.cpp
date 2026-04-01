#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDataStream>
#include "jstp/JstpPayload.hpp"
FILEDISC_BEGIN

JstpPayload::JstpPayload()
    : flag_{}
    , host_{}
{

}

auto JstpPayload::setPair(const QString &key, const QString &value) -> void{
    pairs_.insert(key, value);
}

auto JstpPayload::setHostField(const JstpHostField &host) -> void{
    host_ = host;
    setFlag(FLAG_HOST);
}

auto JstpPayload::pushFileField(const JstpFileField &file) -> void{
    files_.push_back(file);
    setFlag(FLAG_FILES);
}

auto JstpPayload::pushDirField(const JstpDirField &dir) -> void{
    dirs_.push_back(dir);
    setFlag(FLAG_DIRS);
}

auto JstpPayload::getPair(const QString &key) -> QString{
    return pairs_.value(key, "");
}

auto JstpPayload::getHostField() -> JstpHostField{
    return host_;
}

auto JstpPayload::getFileField() -> QVector<JstpFileField>{
    return files_;
}

auto JstpPayload::getDirField() -> QVector<JstpDirField>{
    return dirs_;
}

auto JstpPayload::fromJson(const QString &json) -> ErrBox{
    return fromJson(json.toUtf8());
}

auto JstpPayload::fromJson(const QByteArray &json) -> ErrBox{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(json, &err);
    if(doc.isNull() || err.error != QJsonParseError::NoError){
        return ErrBox(ErrCode::BadJson, "Invalid JSON string: " + err.errorString());
    }
    
    auto obj = doc.object();
    takeHost(obj);
    takeDirs(obj);
    takeFiles(obj);
    takePairs(obj);
    
    return OkBox();
}

auto JstpPayload::hasFlag(qint32 flag) -> bool{
    return (flag_ & flag);
}

auto JstpPayload::setFlag(qint32 flag) -> void{
    flag_ |= flag;
}

auto JstpPayload::unsetFlag(qint32 flag) -> void{
    flag_ &= (~flag);
}

auto JstpPayload::toString() -> QString{
    return QString(toByteArray());
}

/**
 * 将JSTP协议头、JSON长度、JSON内容拼接到一个字节数组中，最终报文形如：
 * [4字节的JSTP头][4字节的JSON长度][N字节的JSON内容]
 */
auto JstpPayload::toSendable() -> QByteArray{
    QByteArray buf;
    QByteArray json = toByteArray();
    QDataStream ds(&buf, QIODevice::WriteOnly);
    
    ds.setByteOrder(QDataStream::LittleEndian); //设置字节序，避免跨平台时因字节序不同导致报文错位
    ds << QString(HEAD).toUtf8();
    ds << static_cast<qint32>(json.size());
    ds << json;
    
    return buf;
}

auto JstpPayload::toByteArray() -> QByteArray{
    QJsonDocument doc;
    QJsonObject top;
    
    fillPairs(top);
    fillHost(top);
    fillFiles(top);
    fillDirs(top);
    
    doc.setObject(top);
    return doc.toJson();
}

auto JstpPayload::takeHost(QJsonObject &obj) -> void{
    host_.ip = 0;
    host_.port = 0;
    unsetFlag(FLAG_HOST);
    
    /* 如果不存在host实体，直接返回 */
    auto val = obj.value(JSTP_HOST);
    obj.take(JSTP_HOST);
    if(val == QJsonValue::Undefined){
        return;
    }
    
    /* 获取对应名称的JSON实体 */
    auto jhost = val.toObject();
    auto jhost_name = jhost.value(JSTP_HOST_NAME);
    auto jhost_ip = jhost.value(JSTP_HOST_IP);
    auto jhost_port = jhost.value(JSTP_HOST_PORT);
    
    /* 取出主机名称、ip字符串和端口 */
    host_.name = jhost_name.toString();
    host_.ip = static_cast<quint32>(QHostAddress(jhost_ip.toString()).toIPv4Address());
    host_.port = static_cast<quint16>(jhost_port.toInt());
    setFlag(FLAG_HOST);
}

auto JstpPayload::takeFiles(QJsonObject &obj) -> void{
    files_.clear();
    unsetFlag(FLAG_FILES);
    
    /* 不存在files实体则直接返回 */
    auto val = obj.take(JSTP_FILES);
    if(val == QJsonValue::Undefined){
        return;
    }
    
    /* 遍历每个元素并转换为JstpFileField */
    auto jfiles = val.toArray();
    for(const auto &jfile : jfiles){
        JstpFileField field;
        auto jobj = jfile.toObject();
        field.name = jobj.value(JSTP_FILES_NAME).toString();
        field.size = static_cast<quint64>(jobj.value(JSTP_FILES_SIZE).toInteger());
        files_.push_back(field);
    }
    
    setFlag(FLAG_FILES);
}

auto JstpPayload::takeDirs(QJsonObject &obj) -> void{
    dirs_.clear();
    unsetFlag(FLAG_DIRS);
    
    /* 不存在dirs实体则直接返回 */
    auto val = obj.take(JSTP_DIRS);
    if(val == QJsonValue::Undefined){
        return;
    }
    
    /* 遍历每个元素并转换为JstpDirField然后保存到dirs */
    auto jdirs = val.toArray();
    for(const auto &jdir : jdirs){
        JstpDirField field;
        auto jobj = jdir.toObject();
        field.name = jobj.value(JSTP_DIRS_NAME).toString();
        dirs_.push_back(field);
    }
    
    setFlag(FLAG_DIRS);
}

auto JstpPayload::takePairs(QJsonObject &obj) -> void{
    /* 遍历对象中剩余的所有键值对并保存到pairs */
    for(auto it = obj.begin(); it != obj.end(); it++){
        auto key = it.key();
        auto val = it.value();
        pairs_.insert(key, val.toString());
    }
}

auto JstpPayload::fillPairs(QJsonObject &obj) -> void{
    for(auto it = pairs_.begin(); it != pairs_.end(); it++){
        obj.insert(it.key(), it.value());
    }
}

auto JstpPayload::fillHost(QJsonObject &obj) -> void{
    if(!hasFlag(FLAG_HOST)) return;  //未设置host时，不进行填充
    
    QJsonObject host;
    host.insert(JSTP_HOST_NAME, host_.name);
    host.insert(JSTP_HOST_IP, QHostAddress(host_.ip).toString());
    host.insert(JSTP_HOST_PORT, host_.port);
    obj.insert(JSTP_HOST, host);
}

auto JstpPayload::fillFiles(QJsonObject &obj) -> void{
    if(!hasFlag(FLAG_FILES)) return;

    QJsonArray jfiles;
    for(const auto &file : files_){
        QJsonObject jobj;
        jobj.insert(JSTP_FILES_NAME, file.name);
        jobj.insert(JSTP_FILES_SIZE, file.size);
        jfiles.push_back(jobj);
    }
    
    obj.insert(JSTP_FILES, jfiles);
}

auto JstpPayload::fillDirs(QJsonObject &obj) -> void{
    if(!hasFlag(FLAG_DIRS)) return;

    QJsonArray jdirs;
    for(const auto &dir : dirs_){
        QJsonObject jobj;
        jobj.insert(JSTP_DIRS_NAME, dir.name);
        jdirs.push_back(jobj);
    }
    
    obj.insert(JSTP_DIRS, jdirs);
}

FILEDISC_END