#ifndef STM32_THIRD_PARTY_H
#define STM32_THIRD_PARTY_H

#include "UTILS/includes.h"
class STM32_Third_PARTY
{
public:
    STM32_Third_PARTY();
    void        setNAME(QString a);
    void        setIS_USED(bool a);
    QString     getNAME();
    bool        getIS_USED();
private:
    QString     NAME;
    bool        IS_USED;

};

#endif // STM32_THIRD_PARTY_H
