#include "stm32_third_party.h"




void        STM32_Third_PARTY::setNAME(QString a){this->NAME =a;}
void        STM32_Third_PARTY::setIS_USED(bool a){this->IS_USED = a;}
QString     STM32_Third_PARTY::getNAME(){return this->NAME;}
bool        STM32_Third_PARTY::getIS_USED(){return this->IS_USED;}
STM32_Third_PARTY::STM32_Third_PARTY()
{
}
