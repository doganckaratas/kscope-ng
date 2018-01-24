#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T18:48:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kscope-ng
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    highlighter.cpp \
    events.cpp

HEADERS  += mainwindow.h \
    highlighter.h \
    events.h

FORMS    += mainwindow.ui

CONFIG   += x86 x86_64

RESOURCES += \
    resources.qrc
