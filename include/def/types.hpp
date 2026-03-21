#ifndef TYPES_HPP
#define TYPES_HPP

#include <QtGlobal>
#include <QPair>
#include "def/err.hpp"
FILEDISC_BEGIN

template<typename V>
using Retval = QPair<V, ErrStruct>;

FILEDISC_END
#endif
