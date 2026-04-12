#ifndef ERR_HPP
#define ERR_HPP

#include <QGlobal.h>
#include <QString>
#include "def/version.hpp"
FILEDISC_BEGIN
/*///////// 定义错误处理相关的数据结构 /////////*/

using ErrStr = QString;

/* 将程序中的错误枚举为错误码 */
enum class ErrCode{
    Ok = 0,
    Busy,  //资源暂不可用
    NoMem, //内存不足
    LocalNetwork,  //本地网络不可用
    Closed,  //文件关闭
    JobInit, //Job初始化错误
    TcpListen, //TCP监听出错
    TcpConne,  //TCP连接出错
    UdpBind,   //UDP绑定出错
    UdpSend,   //UDP发送出错
    BadJson,   //Json格式有误
    
};

/* 错误信息的封装类 */
class ErrBox{
public:
    explicit ErrBox(ErrCode code=ErrCode::Ok);
    explicit ErrBox(ErrCode code, const ErrStr &msg);
    auto errcode() const noexcept -> ErrCode;
    auto errmsg() const noexcept -> ErrStr;
    auto hasError() const noexcept -> bool;
    operator bool() const noexcept;
    
private:
    ErrCode code_;
    ErrStr  msg_;
};

/* 为ErrBox增加一个OkBox的别名。在无错误时使用OkBox返回可以让语义更清晰 */
using OkBox = ErrBox;

FILEDISC_END
#endif
