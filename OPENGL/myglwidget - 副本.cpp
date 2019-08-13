#include "myglwidget.h"
#include "ui_myglwidget.h"
#include <GL/glu.h>


MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::MyGLWidget), mFullScreen(false), mRotateTriangle(0.0f), mRotateQuad(0.0f)
{
    ui->setupUi(this);
    showNormal();
    startTimer(50);
}

MyGLWidget::~MyGLWidget()
{
    delete ui;
}

//下面的代码的作用是重新设置OpenGL场景的大小，而不管窗口的大小是否已经改变(假定您没有使用全屏模式)。
//甚至您无法改变窗口的大小时(例如您在全屏模式下)，它至少仍将运行一次--在程序开始时设置我们的透视图。
//OpenGL场景的尺寸将被设置成它显示时所在窗口的大小。
void MyGLWidget::resizeGL(int width, int height)
{
    if (height == 0) { // 防止被零除
        height = 1; // 将高设为1
    }
//    width = 100;
//    height = 100;
    glViewport(0, 0, width, height); //重置当前的视口
    //下面几行为透视图设置屏幕。意味着越远的东西看起来越小。这么做创建了一个现实外观的场景。
    //此处透视按照基于窗口宽度和高度的45度视角来计算。0.1f，100.0f是我们在场景中所能绘制深度的起点和终点。
    //glMatrixMode(GL_PROJECTION)指明接下来的两行代码将影响projection matrix(投影矩阵)。
    //投影矩阵负责为我们的场景增加透视。 glLoadIdentity()近似于重置。它将所选的矩阵状态恢复成其原始状态。
    //调用glLoadIdentity()之后我们为场景设置透视图。
    //glMatrixMode(GL_MODELVIEW)指明任何新的变换将会影响 modelview matrix(模型观察矩阵)。
    //模型观察矩阵中存放了我们的物体讯息。最后我们重置模型观察矩阵。如果您还不能理解这些术语的含义，请别着急。
    //在以后的教程里，我会向大家解释。只要知道如果您想获得一个精彩的透视场景的话，必须这么做。
    glMatrixMode(GL_PROJECTION);// 选择投影矩阵
    glLoadIdentity();// 重置投影矩阵
    //设置视口的大小
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);	//选择模型观察矩阵
    glLoadIdentity(); // 重置模型观察矩阵
}

//接下的代码段中，我们将对OpenGL进行所有的设置。我们将设置清除屏幕所用的颜色，打开深度缓存，启用smooth shading(阴影平滑)，等等。
//这个例程直到OpenGL窗口创建之后才会被调用。此过程将有返回值。但我们此处的初始化没那么复杂，现在还用不着担心这个返回值。
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
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 白色背景
glClearColor(0.0f, 0.0f, 1.0f, 0.0f); // 蓝色背景
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

//下一段包括了所有的绘图代码。任何您所想在屏幕上显示的东东都将在此段代码中出现。
//以后的每个教程中我都会在例程的此处增加新的代码。如果您对OpenGL已经有所了解的话，您可以在glLoadIdentity()调用之后，
//试着添加一些OpenGL代码来创建基本的形。
//如果您是OpenGL新手，等着我的下个教程。目前我们所作的全部就是将屏幕清除成我们前面所决定的颜色，清除深度缓存并且重置场景。
//我们仍没有绘制任何东东。
void MyGLWidget::paintGL()
{

}


void MyGLWidget::timerEvent(QTimerEvent *event)
{
    //下两行是新增的。倘若把 rtri 和 rquad 想象为容器，那么在程序的开始我们创建了容器( GLfloat rtri , 和 GLfloat rquad )。
    //当容器创建之后，里面是空的。下面的第一行代码是向容器中添加0.2。
    //因此每次当我们运行完前面的代码后，都会在这里使 rtri 容器中的值增长0.2。
    //后面一行将 rquad 容器中的值减少0.15。同样每次当我们运行完前面的代码后，都会在这里使 rquad 容器中的值下跌0.15。
    //下跌最终会导致对象旋转的方向和增长的方向相反。
    //尝试改变下面代码中的+和-，来体会对象旋转的方向是如何改变的。
    //并试着将0.2改成1.0。这个数字越大，物体就转的越快，这个数字越小，物体转的就越慢。
    mRotateTriangle += 0.2f;						// 增加三角形的旋转变量
    mRotateQuad -= 0.15f;						// 减少四边形的旋转变量

    updateGL();

    QGLWidget::timerEvent(event);
}

void MyGLWidget::drawTriangles( )
{
//       填充颜色
//      glColor3f(0.0f,0.0f,1.0f);// 设置当前色为蓝色
//    glTranslatef(-1.5f,0.0f,-6.0f);	// 左移 1.5 单位，并移入屏幕 6.0
    glBegin(GL_TRIANGLES); // 绘制三角形
        glVertex3f(0.0f, 1.0f, 0.0f); // 上顶点
        glVertex3f(-1.0f,-1.0f, 0.0f); // 左下
        glVertex3f( 1.0f,-1.0f, 0.0f); // 右下
    glEnd();
    //因为前面左移了1.5个单位，这次要先向右移回屏幕中心(1.5个单位)，再向右移动1.5个单位。总共要向右移3.0个单位。
//    glTranslatef(3.0f,0.0f,0.0f); // 右移3单位


//    这是一个填充了类似渐变色的三角形
//    glBegin(GL_TRIANGLES);// 绘制三角形
//    //如果您还记得上节课的内容，这段代码在屏幕的左半部分绘制三角形。
//    //下一行代码是我们第一次使用命令glColor3f(r,g,b)。括号中的三个参数依次是红、绿、蓝三色分量。
//    //取值范围可以从0,0f到1.0f。类似于以前所讲的清除屏幕背景命令。
//    //我们将颜色设为红色(纯红色，无绿色，无蓝色)。
//    //接下来的一行代码设置三角形的第一个顶点(三角形的上顶点)，并使用当前颜色(红色)来绘制。
//    //从现在开始所有的绘制的对象的颜色都是红色，直到我们将红色改变成别的什么颜色。
//        glColor3f(1.0f,0.0f,0.0f);// 设置当前色为红色
//        glVertex3f( 0.0f, 1.0f, 0.0f);// 上顶点
//    //第一个红色顶点已经设置完毕。接下来我们设置第二个绿色顶点。三角形的左下顶点被设为绿色。
//        glColor3f(0.0f,1.0f,0.0f);// 设置当前色为绿色
//        glVertex3f(-1.0f,-1.0f, 0.0f);// 左下
//    //在设置第三个也就是最后一个顶点。开始绘制之前将颜色设为蓝色。
//    //这将是三角形的右下顶点。glEnd()出现后，三角形将被填充。
//    //但是因为每个顶点有不同的颜色，因此看起来颜色从每个角喷出，并刚好在三角形的中心汇合，三种颜色相互混合。这就是平滑着色。
//        glColor3f(0.0f,0.0f,1.0f);// 设置当前色为蓝色
//        glVertex3f( 1.0f,-1.0f, 0.0f);// 右下
//    glEnd();// 三角形绘制结束
}

void MyGLWidget::drawQuads( )
{
    glBegin(GL_QUADS);	// 绘制正方形
        glVertex3f(-1.0f, 1.0f, 0.0f);	// 左上
        glVertex3f( 1.0f, 1.0f, 0.0f);	// 右上
        glVertex3f( 1.0f,-1.0f, 0.0f);	// 左下
        glVertex3f(-1.0f,-1.0f, 0.0f);	// 右下
    glEnd(); // 正方形绘制结束
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



