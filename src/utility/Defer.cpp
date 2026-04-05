#include <QtDebug>
#include "utility/Defer.hpp"
FILEDISC_BEGIN

Defer::Defer(DeferFunc df)
    : df_(df)
{

}

Defer::~Defer() noexcept{
    try{
        if(df_){
            df_();
        }
    }
    catch(...){
        qCritical("Critical error in Defer.~Defer(): You SHOULD NOT throw any exceptions.");
    }
}


FILEDISC_END