#ifndef JSTPEMITER_HPP
#define JSTPEMITER_HPP

#include <QObject>
#include "def/version.hpp"
FILEDISC_BEGIN

/*///////// 作为*Job的代理向外界发送信号(*Job不继承QObject，使其可以按更为原生和纯粹的方式实现自身功能) /////////*/
class JstpEmiter : public QObject{
    Q_OBJECT
public:
    
    
signals:
    
};

FILEDISC_END
#endif
