#include "stm32.h"






QString                      STM32::getType(){return this->type;}
QString                      STM32::getPackaging(){return this->packaging;}
QList<STM32_GPIO>*           STM32::getGpios(){return this->gpios;}
QList<STM32_PERIPHERAL>*     STM32::getPeripherals(){return this->peripherals;}
QList<STM32_DRIVER>*         STM32::getDrivers(){return this->drivers;}
QList<STM32_Third_PARTY>*    STM32::getThirds(){return this->thirds;}

void                       STM32::setPackaging(QString a){this->packaging = a;}
void                       STM32::setType(QString a){this->type = a;}
void                       STM32::setGpios(QList<STM32_GPIO>* a){this->gpios = a;}
void                       STM32::setPeripherals(QList<STM32_PERIPHERAL>* a){this->peripherals = a;}
void                       STM32::setDrivers(QList<STM32_DRIVER>*  a){this->drivers = a;}
void                       STM32::setThirds(QList<STM32_Third_PARTY>* a){this->thirds = a;}









STM32::STM32()
{
}
