#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml>
#include <QFile>
#include <QXmlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void parseBlog(QXmlStreamReader &reader);
    void dosomething();
    QString doXpath(const QString &sXmlPath, const QString &sFistLabel, const QString &sSeconLabel, const QString &sThridLabel, QString &errMsg);

private:
    Ui::MainWindow *ui;
    void InitMenuBarUI();
    void InitLeftMenu();
    void InitConsole();
    void InitCentralWidget();
    void setTree(QWidget a);
};

#endif // MAINWINDOW_H
