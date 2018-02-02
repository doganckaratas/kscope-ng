#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T18:48:49
#
#-------------------------------------------------


# Add INSTALLS directives for qscintilla


include(./src/editor/qscintilla.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets printsupport
    CONFIG += c++11
} else {
    QMAKE_CXXFLAGS += -std=c++11
    CONFIG -= android_install
}

# MacOS Hack
unix:macx {
    QT += macextras
}

CONFIG   += x86 x86_64 qt warn_off thread exceptions

TARGET = kscope-ng

TEMPLATE = app

SOURCES +=  \
            ./src/core/main.cpp \
            ./src/core/mainwindow.cpp


HEADERS  += \
            ./src/include/mainwindow.h

INCLUDEPATH += \
            ./src/include \
            ./src/editor/qscintilla \
            ./src/editor/include \
            ./src/editor/lexlib \
            ./src/editor/src

DEFINES += SCINTILLA_QT SCI_LEXER

FORMS    += ./src/view/mainwindow.ui

RESOURCES += ./res/resources.qrc
