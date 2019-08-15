#include "jsonutils.h"
//https://www.cnblogs.com/findumars/p/10332426.html
JsonUtils* JsonUtils::m_instance = 0;






void   JsonUtils::save(QString json,QString path)
{
    qDebug()<<""<<endl;
    OperateCSVFile tools;
    if(!this->jsonString.trimmed().isEmpty())
        tools.appendQstring(this->jsonString,path);
    else
        qDebug()<<"OperateCSVFile tools "<<endl;
}
QString   JsonUtils::read(QString path)
{

}
//  输出结果
//{
//	"Packaging": "",
//	"dirvers": [],
//	"gpios": [{
//			"isUse": "0",
//			"name": "PA0"
//		},
//		{
//			"isUse": "0",
//			"name": "PB0"
//		}
//	],
//	"peripherals": [{
//		"gpios": [{
//				"isUse": "0",
//				"name": "PB12"
//			},
//			{
//				"isUse": "0",
//				"name": "PB13"
//			}
//		],
//		"isUse": "0",
//		"name": "CAN2"
//	}],
//	"thirds": [{
//			"isUse": "0",
//			"name": "EWIN"
//		},
//		{
//			"isUse": "0",
//			"name": "PAI"
//		}
//	],
//	"type": ""
//}
QString   JsonUtils::stm32ToJson(STM32 stm)
{
     QJsonObject stm32Object;
     stm32Object.insert(QStringLiteral("type"), stm.getType());
     stm32Object.insert(QStringLiteral("Packaging"), stm.getPackaging());


    QList<STM32_GPIO>* ios = stm.getGpios();
    if(ios->size() >0 )
        stm32Object.insert(QStringLiteral("gpios"), this->getGPIOJsonArray(ios));


    QJsonArray perArray;
    QList<STM32_PERIPHERAL>* pers = stm.getPeripherals();
    if(Q_NULLPTR != pers)
    for(int i =0 ; i < pers->size();i++)
    {
        QJsonObject per;
        per.insert(QStringLiteral("name"),  ((STM32_PERIPHERAL)pers->at(i)).getPERIPHERAL_NAME());

        if(((STM32_PERIPHERAL)pers->at(i)).getIS_USED())
            per.insert(QStringLiteral("isUse"), "1");
        else
            per.insert(QStringLiteral("isUse"), "0");

        QList<STM32_GPIO>* ios =  (((STM32_PERIPHERAL)pers->at(i)).getGPIO());
        if(Q_NULLPTR != ios)
        {
            if(ios->size() >0 )
                 per.insert(QStringLiteral("gpios"), this->getGPIOJsonArray(ios));
        }
        perArray.append(per);

    }
   stm32Object.insert(QStringLiteral("peripherals"), perArray);


   QJsonArray dirverArray;
   QList<STM32_DRIVER>* dirvers = stm.getDrivers();
   if(Q_NULLPTR != dirvers)
   for(int i =0 ; i < dirvers->size();i++)
   {
       QJsonObject dirver;
       dirver.insert(QStringLiteral("name"),  ((STM32_DRIVER)dirvers->at(i)).getDRIVER_NAME());

       if(((STM32_DRIVER)dirvers->at(i)).getIS_USED())
           dirver.insert(QStringLiteral("isUse"), "1");
       else
           dirver.insert(QStringLiteral("isUse"), "0");
       dirverArray.append(dirver);

   }

   stm32Object.insert(QStringLiteral("dirvers"), dirverArray);



   QJsonArray thirdArray;
   QList<STM32_Third_PARTY>* thirds = stm.getThirds();
   if(Q_NULLPTR != thirds)
   for(int i =0 ; i < thirds->size();i++)
   {
       QJsonObject third;
       third.insert(QStringLiteral("name"),  ((STM32_Third_PARTY)thirds->at(i)).getNAME());

       if(((STM32_Third_PARTY)thirds->at(i)).getIS_USED())
           third.insert(QStringLiteral("isUse"), "1");
       else
           third.insert(QStringLiteral("isUse"), "0");


       thirdArray.append(third);

   }

   stm32Object.insert(QStringLiteral("thirds"), thirdArray);


//   qDebug()<<QJsonDocument(stm32Object).toJson()<<endl;

   this->jsonString.clear();
   this->jsonString = QJsonDocument(stm32Object).toJson();
   return this->jsonString;

}



STM32   JsonUtils::JsonTostm32(const QString &json)
{
//    QString tmp = "{\"Packaging\":\"\",\"dirvers\":[],\"gpios\":[{\"isUse\":\"0\",\"name\":\"PA0\"},{\"isUse\":\"0\",\"name\":\"PB0\"}],\"peripherals\":[{\"gpios\":[{\"isUse\":\"0\",\"name\":\"PB12\"},{\"isUse\":\"0\",\"name\":\"PB13\"}],\"isUse\":\"0\",\"name\":\"CAN2\"}],\"thirds\":[{\"isUse\":\"0\",\"name\":\"EWIN\"},{\"isUse\":\"0\",\"name\":\"PAI\"}],\"type\":\"\"}";

    STM32 stm32;
//    json = tmp;
    QJsonParseError error;
//    const QJsonDocument &document = QJsonDocument::fromJson(tmp.toUtf8(), &error);
    const QJsonDocument &document = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (QJsonParseError::NoError == error.error)
    {
        const QJsonObject  stm32Object = document.object();
        const QString  type = stm32Object.value(QStringLiteral("type")).toString();
        stm32.setType(type);
        const QString  packaging = stm32Object.value(QStringLiteral("Packaging")).toString();
        stm32.setPackaging(packaging);
        const QJsonArray ios = stm32Object.value(QStringLiteral("gpios")).toArray();
        QList<STM32_GPIO>* gpios = new  QList<STM32_GPIO>();
       for ( QJsonValue  value : ios)
       {
           QJsonObject v = value.toObject();
           STM32_GPIO io;
           io.setGPIO_NAME(v.value("name").toString());
           if(v.value("isUse").toString() == "1")
                io.setIS_USED(true);
           else
                io.setIS_USED(false);
           qDebug()<<v.value("name").toString()<<"  "<<v.value("isUse").toString()<<endl;
           gpios->append(io);
       }
       stm32.setGpios(gpios);



       const QJsonArray dirvers = stm32Object.value(QStringLiteral("dirvers")).toArray();
       QList<STM32_DRIVER>* dirs = new QList<STM32_DRIVER>();
       for ( QJsonValue  value : dirvers)
       {
           QJsonObject v = value.toObject();
           STM32_DRIVER dir;
//           t.setNAME(v.value("name").toString());
//           if(v.value("isUse").toString() == "1")
//                t.setIS_USED(true);
//           else
//                t.setIS_USED(false);
//           qDebug()<<v.value("name").toString()<<v.value("isUse").toString()<<endl;
           dirs->append(dir);
       }
       stm32.setDrivers(dirs);


       const QJsonArray peripherals = stm32Object.value(QStringLiteral("peripherals")).toArray();
       QList<STM32_PERIPHERAL>* pers = new QList<STM32_PERIPHERAL>();
       for ( QJsonValue  value : peripherals)
       {
           QJsonObject v = value.toObject();
           STM32_PERIPHERAL per;
           per.setPERIPHERAL_NAME(v.value("name").toString());
           if(v.value("isUse").toString() == "1")
                per.setIS_USED(true);
           else
                per.setIS_USED(false);
//           v.value("gpios").toArray();
           QList<STM32_GPIO>* tmp_ios =this->getGPIOQList( v.value("gpios").toArray());
           per.setGPIO(tmp_ios);
           qDebug()<<v.value("name").toString()<<v.value("isUse").toString()<<endl;
           pers->append(per);
       }
       stm32.setPeripherals(pers);




      const QJsonArray thirds = stm32Object.value(QStringLiteral("thirds")).toArray();
      QList<STM32_Third_PARTY>* ts = new QList<STM32_Third_PARTY>();
      for ( QJsonValue  value : thirds)
      {
          QJsonObject v = value.toObject();
          STM32_Third_PARTY t;
          t.setNAME(v.value("name").toString());
          if(v.value("isUse").toString() == "1")
               t.setIS_USED(true);
          else
               t.setIS_USED(false);
          qDebug()<<v.value("name").toString()<<v.value("isUse").toString()<<endl;
          ts->append(t);
      }
      stm32.setThirds(ts);


    }
//     throw error.errorString();

    return stm32;
}


QList<STM32_GPIO>*  JsonUtils::getGPIOQList(QJsonArray ios)
{
   QList<STM32_GPIO>* gpios = new  QList<STM32_GPIO>();
   for ( QJsonValue  value : ios)
   {
       QJsonObject v = value.toObject();
       STM32_GPIO io;
       io.setGPIO_NAME(v.value("name").toString());
       if(v.value("isUse").toString() == "1")
            io.setIS_USED(true);
       else
            io.setIS_USED(false);
       qDebug()<<"          "<<v.value("name").toString()<<"  "<<v.value("isUse").toString()<<endl;
       gpios->append(io);
   }
   return gpios;
}

QJsonArray JsonUtils::getGPIOJsonArray( QList<STM32_GPIO>* ios )
{
    QJsonArray iosArray;
//    QList<STM32_GPIO>* ios = stm.getGpios();
    if(ios != 0 ){


        for(int i =0 ; i < ios->size();i++)
        {
            QJsonObject io;
            io.insert(QStringLiteral("name"),  ((STM32_GPIO)ios->at(i)).getGPIO_NAME());
            if(((STM32_GPIO)ios->at(i)).getIS_USED())
                io.insert(QStringLiteral("isUse"), "1");
            else
                io.insert(QStringLiteral("isUse"), "0");
            iosArray.append(io);

        }
        return iosArray;
    }
    return iosArray;
}




void JsonUtils::DestoryInstance() {
    if (m_instance != 0) {
        delete m_instance;
        m_instance = 0;
        qDebug()<<"release instance"<<endl;
    }
}


JsonUtils *JsonUtils::GetInstance() {
    if (m_instance == 0) {
        m_instance = new JsonUtils();
    }
    return m_instance;
}

JsonUtils::JsonUtils()
{
}
