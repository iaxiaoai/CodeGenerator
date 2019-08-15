#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "includes.h"
#include "stm32.h"
//#include
class JsonUtils
{
public:
    static JsonUtils                *GetInstance();
    static void                     DestoryInstance();
    QString                         stm32ToJson(STM32 stm);
    STM32                           JsonTostm32(const QString &json);
    void                            save(QString json,QString path);
    QString                         read(QString path);

private:
                                    JsonUtils();
     static JsonUtils*              m_instance;
     QJsonArray                     getGPIOJsonArray( QList<STM32_GPIO>* ios );
     QList<STM32_GPIO>*             getGPIOQList(QJsonArray ios);
     QString                        jsonString;
};

#endif // JSONUTILS_H
