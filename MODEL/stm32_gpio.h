#ifndef STM32_GPIO_H
#define STM32_GPIO_H
#include    "UTILS/includes.h"

class STM32_GPIO
{
public:
    STM32_GPIO();
    void				setGPIO_NAME(QString a);
    void				setGPIO_POSTION(QString a);//???
    void				setIS_USED(bool a);

    QString				getGPIO_NAME();
    QString				getGPIO_POSTION();//???
    bool				getIS_USED();

private:
    QString				GPIO_NAME;
    QString				GPIO_POSTION;//???
    bool				IS_USED;
};

#endif // STM32_GPIO_H
