#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "jstp/JstpPayload.hpp"
FILEDISC_BEGIN

/**
 * 注意，为了避免调用QJsonValue.toString函数时，由非字符串类型的值导致返回空字符串的问题，所有非QString类型的值
 * 都需要先转换为QString再保存到QJson*相关的对象中
 */
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
    
    /* 如果不存在host字段，直接返回 */
    auto val = obj.value(JSTP_HOST);
    obj.take(JSTP_HOST);
    if(val == QJsonValue::Undefined){
        return;
    }
    
    auto jhost = val.toObject();
    auto jhost_ip = jhost.value(JSTP_HOST_IP);
    auto jhost_port = jhost.value(JSTP_HOST_PORT);
    
    /* 取出ip字符串和端口并转换为数字形式 */
    host_.ip = static_cast<quint32>(QHostAddress(jhost_ip.toString()).toIPv4Address());
    host_.port = static_cast<quint16>(jhost_port.toString().toUInt());
    setFlag(FLAG_HOST);
}

auto JstpPayload::takeFiles(QJsonObject &obj) -> void{
    files_.clear();
    unsetFlag(FLAG_FILES);
    
    /* 不存在files字段则直接返回 */
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
        field.size = static_cast<quint64>(jobj.value(JSTP_FILES_SIZE).toString().toULongLong());
        files_.push_back(field);
    }
    
    setFlag(FLAG_FILES);
}

auto JstpPayload::takeDirs(QJsonObject &obj) -> void{
    dirs_.clear();
    unsetFlag(FLAG_DIRS);
    
    /* 不存在dirs字段则直接返回 */
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
    host.insert(JSTP_HOST_IP, QHostAddress(host_.ip).toString());
    host.insert(JSTP_HOST_PORT, QString::number(host_.port));
    obj.insert(JSTP_HOST, host);
}

auto JstpPayload::fillFiles(QJsonObject &obj) -> void{
    if(!hasFlag(FLAG_FILES)) return;

    QJsonArray jfiles;
    for(const auto &file : files_){
        QJsonObject jobj;
        jobj.insert(JSTP_FILES_NAME, file.name);
        jobj.insert(JSTP_FILES_SIZE, QString::number(file.size));
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