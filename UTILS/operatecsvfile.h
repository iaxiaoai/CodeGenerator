/************************************************************
*   食品安全模块界面部分程序
*   作者：WB
*   电话：15900614365
*   公司：上海睿宗仪器设备有限公司
*   OperateCSVFile 模块
*   作用：csv文件操作模块
************************************************************/

#ifndef OPERATECSVFILE_H
#define OPERATECSVFILE_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDebug>

class OperateCSVFile
{
public:
    OperateCSVFile();

    QString GetCSVMsg(int row, int column, QString fileName);    // row:行    column:列
    void ImputCsvMsg(int row, int column, QString string,QString fileName);
    int findRowQStringFromCsvMsg(int colum, QString stringToFind, QString fileName);
    int appendQstring(QString string, QString fileName);
    int getLine(QString fileName);
};

#endif // OPERATECSVFILE_H
