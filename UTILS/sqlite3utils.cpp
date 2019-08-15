#include "sqlite3utils.h"

Sqlite3Utils* Sqlite3Utils::m_instance = 0;
QSqlDatabase Sqlite3Utils::db;

#define databaseConnectionName "data.db"






QList<Category>*                    Sqlite3Utils::fetchCategory()//获取类别信息 初始化项目时调用
{
    QList<Category>* categoryList = new QList<Category>();
    //获取所有GPIO
    QSqlQuery query(db);
    query.prepare("SELECT ID,CATEGORY_NAME,LEVEL,PARENT_ID FROM CATEGORY");
//    query.addBindValue(type);
    bool success = query.exec();
    if(success)
    {
        QSqlRecord  rec =  query.record();
        while(query.next())
        {
             Category c;
             c.setId(query.value(0).toString());
             c.setName(query.value(1).toString());
             c.setLevel(query.value(2).toString());
             c.setPid(query.value(3).toString());
             categoryList->append(c);
        }
    }
    else
    {
        qDebug()<<"获取所有GPIO     !success"<<endl;
    }

    return categoryList;
}


STM32       Sqlite3Utils::fetchSTM32ByType(QString type)//通过型号查询STM32对应的详情信息
{
//    this->fetchAllSTM32List();
    this->stm32List.append("STM32F107RCT6");

    STM32 stm32_example;
    if(this->stm32List.size() == 0)
    {
        this->fetchAllSTM32List();
            qDebug()<<type<<"  该STM32信息没有录入 ~~~~"<<endl;
    }else
    {
        //核对数据库是否有该型号的信息
        if(this->stm32List.contains(type))
        {
             //                      获取所有GPIO
              QList<STM32_GPIO>*  stm_gpios = this->fetchGPIOSByType(type);
              if(stm_gpios->size() >0 )
              {
    //                      qDebug()<<((STM32_GPIO)stm_gpios->at(0)).getGPIO_NAME()<<endl;
                  stm32_example.setGpios(stm_gpios);
              }
             //                      获取所有外设
              QList<STM32_PERIPHERAL>*  stm_pers = this->fetchPERIPHERALByType(type);
              if(stm_pers->size() >0 )
              {
    //                      qDebug()<<((STM32_GPIO)stm_gpios->at(0)).getGPIO_NAME()<<endl;
                  stm32_example.setPeripherals(stm_pers);
              }

              //                      获取第三方系统
               QList<STM32_Third_PARTY>*  stmths = this->fetchThirdByType(type);
               if(stm_pers->size() >0 )
               {
     //                      qDebug()<<((STM32_GPIO)stm_gpios->at(0)).getGPIO_NAME()<<endl;
                   stm32_example.setThirds(stmths);
               }



              qDebug()<<stm32_example.getGpios()->size() << "       " <<stm32_example.getPeripherals()->size()  << "       " <<stm32_example.getThirds()->size()  <<endl;
        }else
        {
            qDebug()<<type<<"  该STM32信息没有录入 ~~~~"<<endl;
        }

    }
    return  stm32_example;
}

//通过型号查询STM32对应的 所有外设
QList<STM32_Third_PARTY>*            Sqlite3Utils::fetchThirdByType(QString type)
{
    QList<STM32_Third_PARTY>* stm_ths = new QList<STM32_Third_PARTY>();

    QSqlQuery query(db);
    query.prepare("SELECT DRIVER_NAME FROM STM32_DRIVER WHERE STM32_ID IN ("
                  "SELECT ID FROM STM32_LIST WHERE TYPE=?) AND CATEGORY = 1");
    query.addBindValue(type);
    bool success = query.exec();
    if(success)
    {
        QSqlRecord  rec =  query.record();
        while(query.next())
        {
//                    int gpiosCol = rec.indexOf("GOIO_LIST"); // index of the field "name"
//                    QString gpios = query.value(gpiosCol).toString();//
             QString thirdName = query.value(0).toString();
             STM32_Third_PARTY t;
             t.setNAME(thirdName);
             t.setIS_USED(false);
             stm_ths->append(t);
        }
    }
    else
    {
        qDebug()<<"获取所有GPIO     !success"<<endl;
    }

    return stm_ths;
}

//通过型号查询STM32对应的 所有外设
QList<STM32_PERIPHERAL>*            Sqlite3Utils::fetchPERIPHERALByType(QString type)
{

    QList<STM32_PERIPHERAL>* stm_pers = new QList<STM32_PERIPHERAL>();

    QSqlQuery query(db);
    query.prepare("SELECT PERIPHERAL_NAME,OCCUPY_GPIO FROM STM32_PERIPHERAL WHERE STM32_ID IN ("
                  "SELECT ID FROM STM32_LIST WHERE TYPE=?)");
    query.addBindValue(type);
    bool success = query.exec();
    if(success)
    {
        QSqlRecord  rec =  query.record();
        while(query.next())
        {

            STM32_PERIPHERAL pre;


            int gpiosCol = rec.indexOf("OCCUPY_GPIO"); // index of the field "name"
            QString gpios = query.value(gpiosCol).toString();//


             if(!gpios.trimmed().isEmpty())
             {
                 QList<STM32_GPIO>*  stm_gpios =  new QList<STM32_GPIO>();
                 QStringList tmp = gpios.split(",");
                 if(tmp.size() > 0)
                 {

                        for(int i=0;i<tmp.size();i++)
                        {
                             STM32_GPIO io;
                             io.setGPIO_NAME(tmp.at(i));
                             io.setIS_USED(false);
                             stm_gpios->append(io);
                        }

                    pre.setGPIO(stm_gpios);
                 }else{
                     qDebug()<<"没有录入GPIO信息"<<endl;
                 }

             }

             int nameCol = rec.indexOf("PERIPHERAL_NAME"); // index of the field "name"
             QString name = query.value(nameCol).toString();//
             pre.setPERIPHERAL_NAME(name);
             pre.setIS_USED(false);
             stm_pers->append(pre);

        }
    }
    else
    {
        qDebug()<<"获取所有GPIO     !success"<<endl;
    }

    return stm_pers;
}

QList<STM32_GPIO>*       Sqlite3Utils::fetchGPIOSByType(QString type)
{

    QList<STM32_GPIO>* stm_gpios = new QList<STM32_GPIO>();

    //获取所有GPIO
    QSqlQuery query(db);
    query.prepare(" SELECT GOIO_LIST FROM STM32_GPIO WHERE STM32_ID IN ( SELECT ID FROM STM32_LIST WHERE TYPE=?)");
    query.addBindValue(type);
    bool success = query.exec();
    if(success)
    {
        QSqlRecord  rec =  query.record();
        while(query.next())
        {
//                    int gpiosCol = rec.indexOf("GOIO_LIST"); // index of the field "name"
//                    QString gpios = query.value(gpiosCol).toString();//
             QString gpios = query.value(0).toString();
             if(!gpios.trimmed().isEmpty())
             {
                 QStringList tmp = gpios.split(",");
                 if(tmp.size() > 0)
                 {

                        for(int i=0;i<tmp.size();i++)
                        {
                             STM32_GPIO io;
                             io.setGPIO_NAME(tmp.at(i));
                             io.setIS_USED(false);
                             stm_gpios->append(io);
                        }


                 }else{
                     qDebug()<<"没有录入GPIO信息"<<endl;
                 }

             }
//                    qDebug()<<gpios<<query.value(0).toString()<<endl;
        }
    }
    else
    {
        qDebug()<<"获取所有GPIO     !success"<<endl;
    }

    return stm_gpios;
}


QStringList Sqlite3Utils::fetchAllSTM32List(void)
{
    QStringList list;
    QSqlQuery query("SELECT TYPE FROM STM32_LIST", db);
    bool success = query.exec();
    if(success)
    {
        QSqlRecord  rec =  query.record();
        while(query.next())
        {
            int typeCol = rec.indexOf("TYPE"); // index of the field "name"
            list.append(query.value(typeCol).toString());

            qDebug()<<list.at(0)<<"----"<<endl;
//            qDebug()<<query.value(idCol).toString()<<"----"<<endl;
        }
    }
    else
    {
        qDebug()<<"!success"<<endl;
    }


    stm32List.append(list);

//    query.clear();
    return list;
}



Sqlite3Utils *Sqlite3Utils::GetInstance() {
    if (m_instance == 0) {
        //使用默认连接
//        QSqlDatabase db = QSqlDatabase::database("QSQLITE");
//        使用自定义连接
        db = QSqlDatabase::addDatabase("QSQLITE");
//        db.setHostName("127.0.0.1");
        db.setDatabaseName(databaseConnectionName);
//        db.setUserName("");
//        db.setPassword("");
        bool ok = db.open();

        if (true           == ok)
        {
            qDebug()<<"is Contain"<<endl;
        }
        else
        {
            qDebug()<<"is not Contain"<<endl;
        }



//        QSqlQuery query("SELECT TYPE, ID FROM STM32_LIST", db);
//        bool success = query.exec();
//        if(success)
//        {
//            QSqlRecord  rec =  query.record();
//            query;
//            while(query.next())
//            {
//                int idCol = rec.indexOf("ID"); // index of the field "name"
//                int typeCol = rec.indexOf("TYPE"); // index of the field "name"
//                qDebug()<<query.value(idCol).toString()<<"----"<<query.value(typeCol).toString()<<endl;
//            }
//        }
//        else
//        {
//            qDebug()<<"!success"<<endl;
//        }

        m_instance = new Sqlite3Utils();

    }
    return m_instance;
}


void Sqlite3Utils::DestoryInstance() {
    if (m_instance != 0) {
        delete m_instance;
        m_instance = 0;
        qDebug()<<"release instance"<<endl;
    }
}


Sqlite3Utils::Sqlite3Utils()
{
}


