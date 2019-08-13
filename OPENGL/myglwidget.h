#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>
#include <QMessageBox>
#include <QApplication>
#include <QTextStream>
#include <math.h>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
protected:
    void resizeGL(int w, int h);

    void initializeGL();

    void paintGL();

    void keyPressEvent(QKeyEvent *event);
private:

    bool mFullScreen;

    void setupWorld();

    void readStr(QTextStream *stream, QString &string);

    void loadTexture();
private:
    bool m_show_full_screen;



    GLfloat m_yrot;
    GLfloat m_xpos;
    GLfloat m_zpos;
    GLfloat m_heading;
    GLfloat m_walkbias;
    GLfloat m_walkbiasangle;
    GLfloat m_lookupdown;
    GLuint	m_filter;
    GLuint	m_texture[3];

    bool m_blend;
};

#endif // MYGLWIDGET_H
