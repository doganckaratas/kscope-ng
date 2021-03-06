#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T18:48:49
#
#-------------------------------------------------


# Add INSTALLS directives for qscintilla

#system(\
#        cd ./cscope && \
#        ./configure && \
#        make -j4 && \
#        mv ./src/cscope ./cscope && \
#        make distclean \
#        )


include(./editor/qscintilla.pri)

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

SOURCES +=  ./core/main.cpp \
            ./core/kscope.cpp \
            ./core/findreplace.cpp \
            ./core/cscope.cpp \
#            ./view/view.cpp \
            ./view/findreplace2.cpp

HEADERS  += ./include/kscope.h \
            ./include/findreplace.h \
            ./include/cscope.h \
#            ./include/view.h \
            ./view/findreplace2.h

INCLUDEPATH += \
            ./include \
            ./view \
            ./editor/qscintilla \
            ./editor/include \
            ./editor/lexlib \
            ./editor/src

DEFINES += SCINTILLA_QT SCI_LEXER

FORMS    += ./view/mainwindow.ui \
            ./view/findreplace.ui \
            ./view/cscope.ui

RESOURCES += ./res/resources.qrc
