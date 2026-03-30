#ifndef JSTPREQUEST_HPP
#define JSTPREQUEST_HPP

#include <QByteArray>
#include "def/req.hpp"
#include "def/types.hpp"
FILEDISC_BEGIN

/*///////// 对JSTP请求的封装，可将JSTP请求转换为JSON(主要)组成的网络报文，也可将JSON结构化为此对象 /////////*/
class JstpRequest{
public:
    using RoByteArray = const QByteArray&;
    
public:
    explicit JstpRequest() = default;    //默认初始化为Test请求
    auto fromJson(const QString &json) -> ErrBox;  //从json字符串中解析出请求信息
    auto type() -> ReqType(); //获取请求类型
    auto beginPath() -> QString; //获取请求起始路径
    auto targetName() -> QString; //获取请求目标名称
    auto setType(ReqType type) -> void;  //设置请求类型
    auto setBeginPath(const QString &path) -> void;   //设置请求的起始路径(例如/home/shared)
    auto setTargetName(const QString &name) -> void;  //设置请求目标的名称(例如image)
    auto asByteArray() -> RoByteArray;  //将此请求转换为QByteArray，以便交由Socket发送
    
private:
    ReqType type_;
    QByteArray data_;
};

FILEDISC_END
#endif
