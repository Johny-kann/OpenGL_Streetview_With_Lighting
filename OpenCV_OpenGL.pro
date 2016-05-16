#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T11:22:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV_OpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwindow.cpp \
    texturemapping.cpp

HEADERS  += mainwindow.h \
    openglwindow.h \
    texturemapping.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
