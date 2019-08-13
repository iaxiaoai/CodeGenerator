#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UTILS/includes.h"
#include "OPENGL/myglwidget.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QDockWidget>
class LeftWidget : public QWidget
{
public:
    QSize sizeHint() const
    {
        return QSize(270, 900); /* 在这里定义dock的初始大小 */
    }
};

class RightWidget : public QWidget
{
public:
    QSize sizeHint() const
    {
        return QSize(200, 900); /* 在这里定义dock的初始大小 */
    }
};


class BottomWidget : public QWidget
{
public:
    QSize sizeHint() const
    {
        return QSize(1200, 120); /* 在这里定义dock的初始大小 */
    }
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(WINDOWS_TITLE);
    setWindowIcon(QIcon(WINDOWS_ICON));

//        MyGLWidget *m = new MyGLWidget(this);

////        m->move((this->width()-m->width())/2,(this->height()-m->height())/2);
////         m->move((this->width()-m->width()),0);

//        m->move(0,0);
//        m->setGeometry(QRect(0,0,(this->width())/2,(this->height())/2));
//        m->show();




    this->InitLeftMenu();
    this->InitConsole();
    this->InitCentralWidget();
    this->InitMenuBarUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InitMenuBarUI()
{
    QMenuBar *menubar = new QMenuBar();

    menubar->setStyleSheet("width:100%;margin-top:5px;background-color:#f0f0f0;");

    //         QMenu *newFile = menubar->addMenu(tr("&NEW"));
    QMenu * newFile = menubar->addMenu("Project");
    QAction *nw = newFile->addAction("New");
    QObject::connect(nw, &QAction::triggered,
                     //Lambda 表达式
                     [=]()
    {
        qDebug() << "已退出";
    }
    );



    newFile->addAction("Open");
    newFile->addAction("Save");
    newFile->addAction("Close");

    QMenu * Setting = menubar->addMenu("Setting");
    Setting->addAction("Setting");

    QMenu * Build = menubar->addMenu("Build");
    Build->addAction("Build for Template");
    Build->addAction("Start this Project");


    QMenu * Window = menubar->addMenu("Window");
    Window->addAction("Reset Windows Layout");
    //Window->addAction("");

    QMenu * Help = menubar->addMenu("Help");
    Help->addAction("Get manunal");
    Help->addAction("About");

    //工具栏
    QAction  *newAction = new QAction(QIcon(TOOLBAR_NEW_ICON), tr("new..."), this);
    newAction->setStatusTip(tr("creat a project"));
    QToolBar *newPrjBar = addToolBar(tr("new"));
    newPrjBar->addAction(newAction);

    QAction  *openAction = new QAction(QIcon(TOOLBAR_OPEN_ICON), tr("open..."), this);
    openAction->setStatusTip(tr("open a project"));
    QToolBar *openPrjBar = addToolBar(tr("open"));
    openPrjBar->addAction(openAction);


    QAction  *saveAction = new QAction(QIcon(TOOLBAR_SAVE_ICON), tr("save..."), this);
    newAction->setStatusTip(tr("save a project"));
    QToolBar *savePrjBar = addToolBar(tr("save"));
    savePrjBar->addAction(saveAction);





    //底部状态栏
    QStatusBar *qSBar = statusBar();
    QLabel *label = new QLabel(this);//分配空间，指定父对象
    label->setText("Normal Text File");
    qSBar->addWidget(label);
    //直接添加，并指定父对象,默认从左到右
    qSBar->addWidget(new QLabel("2",this));
    //从右往左添加：
    qSBar->addPermanentWidget(new QLabel("Coded by chen2511",this));


    this->setMenuBar(menubar);
    //    this->setMenuBar(menubar);
}

void MainWindow::InitLeftMenu()
{

// 左边工具栏1
    QDockWidget *dockWidget = new QDockWidget("外设");
    dockWidget->setStyleSheet("width:300;height:70%;");
    LeftWidget *widget = new LeftWidget();
    widget->setStyleSheet("background-color:gray;");
    dockWidget->setWidget(widget);
    dockWidget->setToolTip("驱动选择");
    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidget);

// 左边工具栏2
    QDockWidget *dockWidget3 = new QDockWidget("驱动和第三方系统");
    dockWidget3->setGeometry(0,0,this->width()/4,this->height());
      dockWidget3->setStyleSheet("width:300;height:30%;");
    LeftWidget *widget3 = new LeftWidget();
    widget3->setStyleSheet("width:300;height:30%;");
    widget3->setStyleSheet("background-color:gray;");
    dockWidget3->setWidget(widget3);
    dockWidget3->setToolTip("外设选择");
//    dockWidget3->sett
    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidget3);
    this->tabifyDockWidget(dockWidget,dockWidget3);

// 右边工具栏2
    QDockWidget *dockWidget2 = new QDockWidget();
    dockWidget2->setGeometry(0,0,this->width()/4,this->height());
    RightWidget *widget2 = new RightWidget();
//    widget->setGeometry(0,0,this->width()/4,this->height());
    widget2->setStyleSheet("background-color:gray;");
    dockWidget2->setWidget(widget2);
    this->addDockWidget(Qt::RightDockWidgetArea,dockWidget2);

}

void MainWindow::InitConsole()
{
    QDockWidget *dockWidget = new QDockWidget("控制台");
    dockWidget->setGeometry(0,0,this->width(),this->height()/4);
    BottomWidget *widget = new BottomWidget();
    widget->setStyleSheet("background-color:gray;");
    dockWidget->setWidget(widget);
    this->addDockWidget(Qt::BottomDockWidgetArea,dockWidget);

    this->setTree(dockWidget);
}

void MainWindow::InitCentralWidget()
{
    QDockWidget *dockWidget = new QDockWidget();
//    dockWidget->setTitleBarWidget();

    MyGLWidget *widget = new MyGLWidget();

//    QWidget *widget = new QWidget();
    widget->setGeometry(0,0,this->width()/2,this->height()/2);
//    widget->setStyleSheet("background-color:blue;");
    this->setCentralWidget(widget);






//    widget->set
//    widget->set
//    dockWidget->setWidget(widget);
//    this->addDockWidget(Qt::BottomDockWidgetArea,dockWidget);
}

void MainWindow::setTree(QDockWidget *container)
{

    // 如果是自定义组件 需要配合
    // peripheralTree->setItemWidget();
    // 使用


    peripheralTree = new QTreeWidget();
    peripheralTree->setHeaderHidden(true);
     peripheralTree->setHeaderLabel(tr("外设列表"));
     QTreeWidgetItem *pRootDeptItem = new QTreeWidgetItem(peripheralTree);
     pRootDeptItem->setText(0, tr("Cities"));


     for(int i = 0 ; i < 10 ; i++)
     {
         QTreeWidgetItem *osloItem = new QTreeWidgetItem(pRootDeptItem);
         QString s ="Oslo :"+QString::number(i);
         osloItem->setText(0, tr(s.toLocal8Bit().data()));
     }


         QTreeWidgetItem *newItem1=new QTreeWidgetItem(peripheralTree);
         newItem1->setText(0,"第一顶部的结点");

         QTreeWidgetItem *newItem2=new QTreeWidgetItem(peripheralTree);
         newItem2->setText(0,"第二顶部的结点");

         QTreeWidgetItem *newItem3=new QTreeWidgetItem(peripheralTree);
         newItem3->setText(0,"第三顶部的结点");

         QTreeWidgetItem *newItem4=new QTreeWidgetItem(peripheralTree);
         newItem4->setText(0,"第四顶部的结点");

         QTreeWidgetItem *newItem5=new QTreeWidgetItem(peripheralTree);
         newItem5->setText(0,"第五顶部的结点");










    container->setWidget(peripheralTree);
}

void MainWindow::parseBlog(QXmlStreamReader &reader) {
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {  // 开始元素
            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "Blog") == 0) {
                qDebug() << QString::fromLocal8Bit("********** 开始元素<Blog> ********** ");
            } else if (QString::compare(strElementName, QStringLiteral("作者")) == 0) {  // 方式一
                reader.readNext();
                if (reader.isCharacters()) {
                    qDebug() << QStringLiteral("作者：%1").arg(reader.text().toString());
                }
            } else if (QString::compare(strElementName, QStringLiteral("主页")) == 0) {  // 方式二
                qDebug() << QStringLiteral("主页：%1").arg(reader.readElementText());
            } else if (QString::compare(strElementName, QStringLiteral("个人说明")) == 0) {
                qDebug() << QStringLiteral("个人说明：%1").arg(reader.readElementText());
            }
        } else if (reader.isEntityReference()) {  // 实体引用
            QString strName = reader.name().toString();
            QString strText = reader.text().toString();
            qDebug() << QString("EntityReference : %1(%2)").arg(strName).arg(strText);
        } else if (reader.isCDATA()) {  // CDATA
            QString strCDATA = reader.text().toString();
            qDebug() << QString("CDATA : %1").arg(strCDATA);

            reader.readNext();
            if (reader.isCharacters()) {
                QString strCharacters = reader.text().toString();
                qDebug() << QString("Characters : %1").arg(strCharacters);
            }
        } else if (reader.isEndElement()) {  // 结束元素
            QString strElementName = reader.name().toString();
            if (QString::compare(strElementName, "Blogs") == 0) {
                qDebug() << QString::fromLocal8Bit("********** 结束元素<Blogs> ********** ");
                break;  // 跳出循环（解析 QXmlStreamReader::EndDocument）
            } else if (QString::compare(strElementName, "Blog") == 0) {
                qDebug() << QString::fromLocal8Bit("********** 结束元素<Blog> ********** ");
            }
        }
    }
}

void MainWindow::dosomething()
{



    QFile file("C:\\Users\\liulei\\Desktop\\baidu.html");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // 以只写模式打开文件
        QXmlStreamReader reader(&file);

        // 解析 XML，直到结束
        while (!reader.atEnd()) {

            // 读取下一个元素
            QXmlStreamReader::TokenType nType = reader.readNext();

            switch (nType) {
            case QXmlStreamReader::StartDocument: {  // 开始文档
                qDebug() << QString::fromLocal8Bit("********** 开始文档（XML 声明） ********** ");
                // XML 声明
                QString strVersion = reader.documentVersion().toString();
                QString strEncoding = reader.documentEncoding().toString();
                bool bAlone = reader.isStandaloneDocument();
                qDebug() << QString::fromLocal8Bit("版本：%1  编码：%2  Standalone：%3")
                            .arg(strVersion).arg(strEncoding).arg(bAlone) << "\r\n";
                break;
            }
            case QXmlStreamReader::Comment: {  // 注释
                qDebug() << QString::fromLocal8Bit("********** 注释 ********** ");
                QString strComment = reader.text().toString();
                qDebug() << strComment << "\r\n";
                break;
            }
            case QXmlStreamReader::ProcessingInstruction: {  // 处理指令
                qDebug() << QString::fromLocal8Bit("********** 处理指令 ********** ");
                QString strProcInstr = reader.processingInstructionData().toString();
                qDebug() << strProcInstr << "\r\n";
                break;
            }
            case QXmlStreamReader::DTD: {   // DTD
                qDebug() << QString::fromLocal8Bit("********** DTD ********** ");
                QString strDTD = reader.text().toString();
                QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // 符号声明
                QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // 实体声明
                // DTD 声明
                QString strDTDName = reader.dtdName().toString();
                QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD 公开标识符
                QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD 系统标识符
                qDebug() << QString::fromLocal8Bit("DTD : %1").arg(strDTD);
                qDebug() << QString::fromLocal8Bit("DTD 名称 : %1").arg(strDTDName);
                qDebug() << QString::fromLocal8Bit("DTD 公开标识符 : %1").arg(strDTDPublicId);
                qDebug() << QString::fromLocal8Bit("DTD 系统标识符 : %1").arg(strDTDSystemId);
                qDebug() << "\r\n";

                break;
            }
            case QXmlStreamReader::StartElement: {  // 开始元素
                QString strElementName = reader.name().toString();
                if (QString::compare(strElementName, "Blogs") == 0) {  // 根元素
                    qDebug() << QString::fromLocal8Bit("********** 开始元素<Blogs> ********** ");
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("Version")) {
                        QString strVersion = attributes.value("Version").toString();
                        qDebug() << QString::fromLocal8Bit("属性：Version(%1)").arg(strVersion);
                    }

                    parseBlog(reader);
                }
                break;
            }
            case QXmlStreamReader::EndDocument: {  // 结束文档
                qDebug() << QString::fromLocal8Bit("********** 结束文档 ********** ");
                break;
            }
            }
        }

        if (reader.hasError()) {  // 解析出错
            qDebug() << QString::fromLocal8Bit("错误信息：%1  行号：%2  列号：%3  字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
        }

        file.close();  // 关闭文件
    }

}


QString MainWindow::doXpath(const QString& sXmlPath,
                            const QString& sFistLabel,
                            const QString& sSeconLabel,
                            const QString& sThridLabel, QString& errMsg)
{

        QXmlQuery query;
        QString sOptionSettings;
        QDomDocument configxmldoc;
        QDomNodeList  sitemNodes;


        QFile db(sXmlPath);
        if ( ! db.exists()) {
            errMsg = "Xml文件未找到！";
            return errMsg;
        }

        if (!db.open(QIODevice::ReadOnly | QIODevice::Text)){
            errMsg = "文件打不开！";
            return errMsg;
        }

        query.setFocus(&db);
        query.setQuery("tree[@id='0']/item[@text='"+sFistLabel+"']/item[@text='"+sSeconLabel+"']/userdata[@name='value']");

        if ( !query.isValid()){
            errMsg = "查询参数有误！";
            return errMsg;
        }


        query.evaluateTo(&sOptionSettings);
        db.close();

         sOptionSettings = sOptionSettings.replace("<","<").replace(">",">").replace("&","&");
         sOptionSettings = sOptionSettings.replace("<userdata name=\"value\">","");
         sOptionSettings = sOptionSettings.replace("</userdata>","");

         //此时sOptionSettings是一个完整的xml语句

        configxmldoc.setContent(sOptionSettings);

        sitemNodes = configxmldoc.elementsByTagName("item");

        for (int i = 0; i < sitemNodes.count(); i++) {
            QDomNode node = sitemNodes.at(i);
            QString itemlabel = node.toElement().attribute("label");
            if (itemlabel == sThridLabel ){
                    QString itemtype = node.toElement().attribute("type");
                    if(itemtype == "checkbox" || itemtype == "radio") {
                        QString itemchecked = node.toElement().attribute("checked");
                        if (itemchecked == "true"){
                            return "1";
                        }
                        else{
                            return "0";
                        }
                    }//end if

                    if (itemtype == "input") {
                        QString itemvalue = node.toElement().attribute("value");
                        return itemvalue;
                    }//end if

                    if (itemtype == "select"){
                        QDomNodeList  optionlist = node.toElement().childNodes();
                        for (int j = 0 ; j < optionlist.count() ; j++) {
                            QDomNode optionnode = optionlist.at(j);
                            QString optionchecked = optionnode.toElement().attribute("selected");
                            if (optionchecked == "true"){
                                QString optionvalue = optionnode.toElement().attribute("value");
                                return optionvalue;
                            }

                        }//end for
                    }//end if

                }//end if
            }//end for

        return "";

}



