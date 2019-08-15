#include "stm32_driver.h"



void 	     STM32_DRIVER::setDRIVER_NAME(QString a){this->DRIVER_NAME = a;}
void 	     STM32_DRIVER::setIS_USED(bool a){this->IS_USED = a;}
QString      STM32_DRIVER::getDRIVER_NAME(){return this->DRIVER_NAME;}
bool         STM32_DRIVER::getIS_USED(){return this->IS_USED;}
QList<STM32_GPIO>*           STM32_DRIVER::getGPIO(){return this->GPIO;}
void                        STM32_DRIVER::setGPIO(QList<STM32_GPIO>* a){this->GPIO = a;}


STM32_DRIVER::STM32_DRIVER()
{
}
