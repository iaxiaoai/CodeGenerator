#include "mainwindow.h"
#include <QApplication>
//#include "OPENGL/mainwidget.h"

//#version 330
//uniform mat4 uPMatrix,uVMatrix,uMMatrix;
//layout (location = 0) in vec3 aPosition;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    gl_Position = uPMatrix * uVMatrix * uMMatrix * vec4(aPosition,1);

    MainWindow w;
    //    w.dosomething();
    //    w.doXpath();

    QString sfist = "工作目录";
    QString ssecond = "工作目录";
    QString sthird = "全路径";
    QString sXmlPath = "C:\\Users\\liulei\\Desktop\\test.xml";


    QString strErrMsg = "";

    w.doXpath(sXmlPath,sfist,ssecond,sthird, strErrMsg);

    //    MainWidget w;
    //    w.showFullScreen();
    w.showMaximized();
    w.show();









    return a.exec();
}

