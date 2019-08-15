#ifndef STM32_H
#define STM32_H

#include "UTILS/includes.h"

#include "Model/stm32_driver.h"
#include "Model/stm32_peripheral.h"
#include "Model/stm32_gpio.h"
#include "Model/stm32_third_party.h"


class STM32
{
public:
    STM32();
    void                            setType(QString a);
    void                            setGpios(QList<STM32_GPIO>* a);
    void                            setPeripherals(QList<STM32_PERIPHERAL>* a);
    void                            setDrivers(QList<STM32_DRIVER>*  a);
    void                            setThirds(QList<STM32_Third_PARTY>* a);
    void                            setPackaging(QString a);

    QString                         getType();
    QList<STM32_GPIO>*              getGpios();
    QList<STM32_PERIPHERAL>*        getPeripherals();
    QList<STM32_DRIVER>*            getDrivers();
    QList<STM32_Third_PARTY>*       getThirds();
    QString                         getPackaging();

private:
    QString                         type;//型号 F107RCT6
    QString                         packaging;//封装 64
    QList<STM32_GPIO>               *gpios;//拥有的IO口,其应该包括 是否被使用的属性
    QList<STM32_PERIPHERAL>         *peripherals;//已实现的外设接口，
    QList<STM32_DRIVER>             *drivers;//已实现的驱动结构
    QList<STM32_Third_PARTY>        *thirds; //已实现的第三方系统

};

#endif // STM32_H
