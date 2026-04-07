#ifndef DEFER_HPP
#define DEFER_HPP

#include <functional>
#include "def/version.hpp"
FILEDISC_BEGIN

/*///////// 将指定的调用DeferFunc推迟到此对象离开析构时执行 /////////*/
using DeferFunc = std::function<void()>;
class Defer{
public:
    explicit Defer(DeferFunc df);
    ~Defer() noexcept;
    Defer(const Defer &other) =delete;   //避免因为拷贝导致的重复调用
    Defer& operator=(const Defer &other) =delete;
private:
    DeferFunc df_;
};

FILEDISC_END
#endif