#ifndef SQLITE3UTILS_H
#define SQLITE3UTILS_H

#include "UTILS/includes.h"
#include "stm32.h"
#include "MODEL/category.h"


class Sqlite3Utils
{
public:

    static Sqlite3Utils *GetInstance();
    static void DestoryInstance();

    QStringList                         fetchAllSTM32List(void);//获取型号列表
    STM32                               fetchSTM32ByType(QString type);//通过型号查询STM32对应的详情信息
    QList<STM32_GPIO>*                  fetchGPIOSByType(QString type);//通过型号查询STM32对应的 所有GPIO
    QList<STM32_PERIPHERAL>*            fetchPERIPHERALByType(QString type);//通过型号查询STM32对应的 所有外设
    QList<STM32_Third_PARTY>*           fetchThirdByType(QString type);//通过型号查询STM32对应的 所有外设

    QList<Category>*                    fetchCategory();//获取类别信息
private:


    Sqlite3Utils();
    QStringList stm32List;
    static Sqlite3Utils* m_instance;
    static QSqlDatabase db;
};

#endif // SQLITE3UTILS_H
