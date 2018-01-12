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
    mainwindow_event_handler.cpp

HEADERS  += mainwindow.h \
    mainwindow_event_handler.h

FORMS    += mainwindow.ui

CONFIG   += x86 x86_64

RESOURCES += \
    resources.qrc
