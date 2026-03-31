#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
}

auto JstpPayload::pushFileField(const JstpFileField &file) -> void{
    files_.push_back(file);
}

auto JstpPayload::pushDirField(const JstpDirField &dir) -> void{
    dirs_.push_back(dir);
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
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(json, &err);
    if(doc.isNull() || err.error() != QJsonParseError::NoError){
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
    
}

auto JstpPayload::toByteArray() -> QByteArray{

}

auto JstpPayload::takeHost(QJsonObject &obj) -> void{
    host_.ip = 0;
    host_.port = 0;
    unsetFlag(FLAG_HOST);
    
    /* 如果不存在host，直接返回 */
    auto val = obj.value(JSTP_HOST);
    obj.remove(JSTP_HOST);
    if(val == QJsonValue::Undefined){
        return;
    }
    
    auto host = val.toObject();
    auto host_ip = host.value(JSTP_HOST_IP);
    auto host_port = host.value(JSTP_HOST_PORT);
    
    host_.ip = static_cast<quint32>(host_ip.toString().toUInt());
    host_.port = static_cast<quint16>(host_port.toString().toUInt());
    setFlag(FLAG_HOST);
}

auto JstpPayload::takeFiles(QJsonObject &obj) -> void{
    files_.clear();
    unsetFlag(FLAG_FILES);
    
    /* 不存在files字段则直接返回 */
    auto val = obj.value(JSTP_FILES);
    obj.remove(JSTP_FILES);
    if(val == QJsonValue::Undefined){
        return;
    }
    
    /* 遍历每个元素并转换为JstpFileField */
    auto files = val.toArray();
    for(const auto &file : files){
        JstpFileField field;
        auto fobj = file.toObject();
        field.name = fobj.value(JSTP_FILES_NAME).toString();
        field.size = static_cast<quint64>(fobj.value(JSTP_FILES_SIZE).toString().toULongLong());
        files_.push_back(field);
    }
    
    setFlag(FLAG_FILES);
}

auto JstpPayload::takeDirs(QJsonObject &obj) -> void{
    dirs_.clear();
    unsetFlag(FLAG_DIRS);
    
    /* 不存在dirs字段则直接返回 */
    auto val = obj.value(JSTP_DIRS);
    obj.remove(JSTP_DIRS);
    if(val == QJsonValue::Undefined){
        return;
    }
    
    /* 遍历每个元素并转换为JstpDirField */
    auto dirs = val.toArray();
    for(const auto &dir : dirs){
        JstpDirField field;
        auto dobj = dir.toObject();
        field.name = dobj.value(JSTP_DIRS_NAME).toString();
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

FILEDISC_END