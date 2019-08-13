#include <QApplication>
#include <QDebug>
#include <GL/glu.h>
#include "OPENGL/myglwidget.h"




const float piover180 = 0.0174532925f;

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent), m_show_full_screen(false), m_yrot(0.0f),
    m_xpos(0.0f), m_zpos(0.0f), m_heading(0.0f), m_walkbias(0.0f),
    m_walkbiasangle(0.0f), m_lookupdown(0.0f), m_filter(0),m_blend(false),mFullScreen(false)
{
    showMaximized();
//    show
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::resizeGL(int w, int h)
{
//    if(h == 0)// 防止被零除
//    {
//        h = 1;// 将高设为1
//    }
    glViewport(0, 0, w, h); //重置当前的视口

//    glMatrixMode(GL_PROJECTION);// 选择投影矩阵
//    glLoadIdentity();// 重置投影矩阵
//    //设置视口的大小
//    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

//    glMatrixMode(GL_MODELVIEW);	//选择模型观察矩阵
//    glLoadIdentity(); // 重置模型观察矩阵
}


void MyGLWidget::initializeGL()
{
    //下一行启用smooth shading(阴影平滑)。阴影平滑通过多边形精细的混合色彩，并对外部光进行平滑。
    //我将在另一个教程中更详细的解释阴影平滑。
    glShadeModel(GL_SMOOTH); // 启用阴影平滑

    //下一行设置清除屏幕时所用的颜色。如果您对色彩的工作原理不清楚的话，我快速解释一下。
    //色彩值的范围从0.0f到1.0f。0.0f代表最黑的情况，1.0f就是最亮的情况。
    //glClearColor 后的第一个参数是Red Intensity(红色分量),第二个是绿色，第三个是蓝色。
    //最大值也是1.0f，代表特定颜色分量的最亮情况。最后一个参数是Alpha值。当它用来清除屏幕的时候，我们不用关心第四个数字。
    //现在让它为0.0f。我会用另一个教程来解释这个参数。
    //通过混合三种原色(红、绿、蓝)，您可以得到不同的色彩。希望您在学校里学过这些。
    //因此，当您使用glClearColor(0.0f,0.0f,1.0f,0.0f)，您将用亮蓝色来清除屏幕。
    //如果您用 glClearColor(0.5f,0.0f,0.0f,0.0f)的话，您将使用中红色来清除屏幕。不是最亮(1.0f)，也不是最暗 (0.0f)。
    //要得到白色背景，您应该将所有的颜色设成最亮(1.0f)。要黑色背景的话，您该将所有的颜色设为最暗(0.0f)。
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 蓝色背景

    //接下来的三行必须做的是关于depth buffer(深度缓存)的。将深度缓存设想为屏幕后面的层。
    //深度缓存不断的对物体进入屏幕内部有多深进行跟踪。
    //我们本节的程序其实没有真正使用深度缓存，但几乎所有在屏幕上显示3D场景OpenGL程序都使用深度缓存。
    //它的排序决定那个物体先画。这样您就不会将一个圆形后面的正方形画到圆形上来。深度缓存是OpenGL十分重要的部分。
    glClearDepth(1.0f);	// 设置深度缓存
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glDepthFunc(GL_LEQUAL);	// 所作深度测试的类型

    //接着告诉OpenGL我们希望进行最好的透视修正。这会十分轻微的影响性能。但使得透视图看起来好一点。
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 告诉系统对透视进行修正
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清除屏幕和深度缓存
    glLoadIdentity();	// 重置当前的模型观察矩阵
}


void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_F2:
    {
        mFullScreen = !mFullScreen;
        if(mFullScreen) {
            showFullScreen();
        }
        else {
            showNormal();
        }
        updateGL();
        break;
    }
    case Qt::Key_Escape:
    {
        qApp->exit();
        break;
    }
    }
}


void MyGLWidget::setupWorld()
{

}
