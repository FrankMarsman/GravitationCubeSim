#-------------------------------------------------
#
# Project created by QtCreator 2016-12-20T18:54:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GravitySim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vector2d.cpp \
    gravsim.cpp

HEADERS  += mainwindow.h \
    vector2d.h \
    gravsim.h

FORMS    += mainwindow.ui
