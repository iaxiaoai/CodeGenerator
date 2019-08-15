#include "operatecsvfile.h"

OperateCSVFile::OperateCSVFile()
{
}

QString OperateCSVFile::GetCSVMsg(int row, int column, QString fileName)
{
    QString temp;
    temp.clear();
    QFile myFile(fileName);
    if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return temp;
    }
    QTextStream in(&myFile);
    QStringList list;
    int i = 0;
    while (!in.atEnd())
    {
        QString fileLine = in.readLine();
        list = fileLine.split(",", QString::SkipEmptyParts);

            if (i == row)
            {
                temp = list.at(column);
                break;
            }
            else
            {
                i++;
            }
        }


    myFile.close();

    return temp;
}

void OperateCSVFile::ImputCsvMsg(int row, int column, QString string, QString fileName)
{
    QString strAll;
    strAll.clear();
    QStringList strList;
    strList.clear();
    QStringList strTemp;
    strTemp.clear();
    // 只读的方式打开文件
    QFile readFile(fileName);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    else
    {
        QTextStream stream(&readFile);
        // 所有的内容存入strall
        strAll = stream.readAll();
    }
    readFile.close();
    // 只写的方式打开文件
    QFile writeFile(fileName);
    if (!writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return;
    }
    else
    {
        QTextStream stream(&writeFile);
        // 以回车的方式存入strlist数组中
        strList = strAll.split("\n");
        for (int i = 0; i < strList.count()-1; i++)
        {
            if (i == row)   // 找到那一行
            {
                strTemp = strList.at(i).split(",", QString::SkipEmptyParts);
                for (int j = 0; j <strTemp.count(); j++)
                {
                    if (j == column)
                    {
                        stream << string;
                    }
                    else
                    {
                        stream << strTemp.at(j);
                    }
                    if (j < strTemp.count()-1)
                    {
                        stream <<  ',';
                    }
                }
                stream << "\n";
            }
            else
            {
                stream << strList.at(i) << "\n";
            }
        }
        writeFile.close();
    }
}

int OperateCSVFile::findRowQStringFromCsvMsg(int colum, QString stringToFind, QString fileName)
{
    QFile myFile(fileName);
    QString strAll;
    int result;
    result = -1;
    strAll.clear();
    if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result = -1;
        return result;
    }
    QTextStream in(&myFile);
    QStringList strList, tempList;
    strAll = in.readAll();
    strList = strAll.split("\n");
//    qDebug() << strList.count() << endl;
    for (int i = 0; i < strList.count()-1; i++)
    {
        tempList = strList.at(i).split(",", QString::SkipEmptyParts);
        if (tempList.at(colum) == stringToFind)
        {
            result = i;
            break;
        }
    }
    myFile.close();
    return result;
}

int OperateCSVFile::appendQstring(QString string, QString fileName)
{
    QFile myFile(fileName);
    if (!myFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        return -1;
        qDebug() << "openfail";
    }
    qDebug() << "ok--------------"<<endl;
    QTextStream in(&myFile);
    in << string;
    myFile.close();
    return 0;
}

int OperateCSVFile::getLine(QString fileName)
{
    QFile myFile(fileName);
    if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return -1;
    }
    QTextStream out(&myFile);
    int i = 0;
    while (!out.atEnd())
    {
        out.readLine();
        i++;
    }
    myFile.close();
    return i;
}
