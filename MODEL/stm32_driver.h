#ifndef STM32_DRIVER_H
#define STM32_DRIVER_H
#include "UTILS/includes.h"
#include "Model/stm32_gpio.h"

class STM32_DRIVER
{
public:
    STM32_DRIVER();

    void 	     setDRIVER_NAME(QString a);
    void 	     setIS_USED(bool a);
    QString      getDRIVER_NAME();
    bool         getIS_USED();
    QList<STM32_GPIO>*           getGPIO();
    void                        setGPIO(QList<STM32_GPIO>* a);

private:
    QString      DRIVER_NAME;
    bool         IS_USED;
    QList<STM32_GPIO>*  GPIO;
};

#endif // STM32_DRIVER_H
