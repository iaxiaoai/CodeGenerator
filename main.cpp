#include "mainwindow.h"
#include <QApplication>
//#include "OPENGL/mainwidget.h"

//#version 330
//uniform mat4 uPMatrix,uVMatrix,uMMatrix;
//layout (location = 0) in vec3 aPosition;

#include "UTILS/sqlite3utils.h"
#include "UTILS/jsonutils.h"

//void digui(QList<Category>* list)
//{
//    for(int i = 0 ; i < list->size() ; i ++)
//    {
//        if(((Category)list->at(i)).getPid() != "0")
//        {
//            if()
//            digui(list);
//        }
//    }
//}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    gl_Position = uPMatrix * uVMatrix * uMMatrix * vec4(aPosition,1);

    //    MainWindow w;
    //    QString sfist = "工作目录";
    //    QString ssecond = "工作目录";
    //    QString sthird = "全路径";
    //    QString sXmlPath = "C:\\Users\\liulei\\Desktop\\test.xml";
    //    QString strErrMsg = "";
    //    w.doXpath(sXmlPath,sfist,ssecond,sthird, strErrMsg);
    //    w.showMaximized();
    //    w.show();



    Sqlite3Utils *sqlite =  Sqlite3Utils::GetInstance();
//    sqlite->fetchAllSTM32List();
//    sqlite->fetchSTM32ByType("STM32F107RCT6");
//    QList<Category>* list = sqlite->fetchCategory();
//    qDebug()<<list->size()<<endl;


    JsonUtils::GetInstance()->stm32ToJson(sqlite->fetchSTM32ByType("STM32F107RCT6"));
//    QString tmp = "{\"Packaging\":\"\",\"dirvers\":[],\"gpios\":[{\"isUse\":\"0\",\"name\":\"PA0\"},{\"isUse\":\"0\",\"name\":\"PB0\"}],\"peripherals\":[{\"gpios\":[{\"isUse\":\"0\",\"name\":\"PB12\"},{\"isUse\":\"0\",\"name\":\"PB13\"}],\"isUse\":\"0\",\"name\":\"CAN2\"}],\"thirds\":[{\"isUse\":\"0\",\"name\":\"EWIN\"},{\"isUse\":\"0\",\"name\":\"PAI\"}],\"type\":\"\"}";
//    JsonUtils::GetInstance()->JsonTostm32(tmp);
    JsonUtils::GetInstance()->save("","C:\\a.json");
    return a.exec();
}

