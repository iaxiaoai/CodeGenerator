#include "stm32_peripheral.h"





QString                      STM32_PERIPHERAL::getPERIPHERAL_NAME(){return this->PERIPHERAL_NAME;}
bool                         STM32_PERIPHERAL::getIS_USED(){return this->IS_USED;}
QList<STM32_GPIO>*           STM32_PERIPHERAL::getGPIO(){return this->GPIO;}

void                        STM32_PERIPHERAL::setPERIPHERAL_NAME(QString a){this->PERIPHERAL_NAME = a;}
void                        STM32_PERIPHERAL::setIS_USED(bool a){this->IS_USED = a;}
void                        STM32_PERIPHERAL::setGPIO(QList<STM32_GPIO>* a){this->GPIO = a;}


STM32_PERIPHERAL::STM32_PERIPHERAL()
{
}
