#-------------------------------------------------
#
# Project created by QtCreator 2019-08-08T14:36:18
#
#-------------------------------------------------

QT       += core gui opengl
QT       += xml
QT       += xmlpatterns
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    OPENGL/myglwidget.cpp \
    UTILS/xmlutils.cpp \
    UTILS/sqlite3utils.cpp \
    stm32.cpp \
    MODEL/stm32_gpio.cpp \
    MODEL/stm32_peripheral.cpp \
    MODEL/stm32_driver.cpp \
    MODEL/stm32_third_party.cpp \
    MODEL/category.cpp \
    UTILS/jsonutils.cpp \
    UTILS/operatecsvfile.cpp

HEADERS  += mainwindow.h \
    UTILS/includes.h \
    UTILS/defines.h \
    UTILS/genericrender.h \
    OPENGL/myglwidget.h \
    UTILS/xmlutils.h \
    UTILS/sqlite3utils.h \
    stm32.h \
    MODEL/stm32_gpio.h \
    MODEL/stm32_peripheral.h \
    MODEL/stm32_driver.h \
    MODEL/stm32_third_party.h \
    MODEL/category.h \
    UTILS/jsonutils.h \
    UTILS/operatecsvfile.h

FORMS    += \
    OPENGL/mainwidget.ui \
    OPENGL/myglwidget.ui

OTHER_FILES += \
    README/README.txt \
    README/GIT√¸¡Ó.txt

RESOURCES += \
    ASSETS/assets.qrc



CONFIG += c++11 #‰ΩéÁâàÊú¨ÊîØÊåÅLAMDAË°®Ëææ
