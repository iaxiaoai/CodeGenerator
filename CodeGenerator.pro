#-------------------------------------------------
#
# Project created by QtCreator 2019-08-08T14:36:18
#
#-------------------------------------------------

QT       += core gui opengl
QT       += xml
QT       += xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    OPENGL/myglwidget.cpp

HEADERS  += mainwindow.h \
    UTILS/includes.h \
    UTILS/defines.h \
    UTILS/genericrender.h \
    OPENGL/myglwidget.h

FORMS    += \
    OPENGL/mainwidget.ui \
    OPENGL/myglwidget.ui

OTHER_FILES += \
    README/README.txt

RESOURCES += \
    ASSETS/assets.qrc



CONFIG += c++11 #低版本支持LAMDA表达
