#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>

namespace Ui {
class MyGLWidget;
}

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
    void timerEvent(QTimerEvent *event);
private:
    Ui::MyGLWidget *ui;
    bool mFullScreen;

    GLfloat mRotateTriangle;
    GLfloat mRotateQuad;

    void drawTriangles( );
    void drawQuads( );
protected:

    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MYGLWIDGET_H
