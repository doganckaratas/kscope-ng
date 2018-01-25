#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T18:48:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kscope-ng
TEMPLATE = app

SOURCES +=  ./src/core/main.cpp \
            ./src/core/mainwindow.cpp \
            ./src/core/highlighter.cpp

HEADERS  += ./src/include/mainwindow.h \
            ./src/include/highlighter.h

FORMS    += ./src/view/mainwindow.ui

RESOURCES += ./res/resources.qrc

CONFIG   += x86 x86_64
