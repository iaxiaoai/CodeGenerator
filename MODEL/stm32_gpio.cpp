#include "stm32_gpio.h"




QString				STM32_GPIO::getGPIO_NAME(){return this->GPIO_NAME;}
QString				STM32_GPIO::getGPIO_POSTION(){return this->GPIO_POSTION;}
bool				STM32_GPIO::getIS_USED(){return this->IS_USED;}

void				STM32_GPIO::setGPIO_NAME(QString a){this->GPIO_NAME = a;}
void				STM32_GPIO::setGPIO_POSTION(QString a){this->GPIO_POSTION = a;}
void				STM32_GPIO::setIS_USED(bool a){this->IS_USED = a;}







STM32_GPIO::STM32_GPIO()
{
}
