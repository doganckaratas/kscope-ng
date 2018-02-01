#!/bin/bash

qmake -makefile -o "Makefile.qscintilla" "CONFIG += qscintilla" src/editor/qscintilla.pri && qmake -makefile -o "Makefile.kscope" "CONFIG += kscope" kscope-ng.pro && (make -f Makefile.qscintilla all clean &) && (make -f Makefile.kscope all clean &) && rm Makefile.qscintilla Makefile.kscope
