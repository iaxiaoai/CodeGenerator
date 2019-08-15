#ifndef STM32_PERIPHERAL_H
#define STM32_PERIPHERAL_H

#include "UTILS/includes.h"
#include "Model/stm32_gpio.h"
class STM32_PERIPHERAL
{
public:
    STM32_PERIPHERAL();


    QString                     getPERIPHERAL_NAME();
    bool                        getIS_USED();
    QList<STM32_GPIO>           *getGPIO();

    void                        setPERIPHERAL_NAME(QString a);
    void                        setIS_USED(bool a);
    void                        setGPIO(QList<STM32_GPIO>* a);
private:
    QString                     PERIPHERAL_NAME;
    bool                        IS_USED;
    QList<STM32_GPIO>           *GPIO;
};

#endif // STM32_PERIPHERAL_H
