#!/bin/bash

# This build script should work only on POSIX systems
# e.g. Linux, MacOS etc..
# it might not compliant with Windows

qmake -makefile -o "Makefile.qscintilla" "CONFIG += qscintilla" src/editor/qscintilla.pri && qmake -makefile -o "Makefile.kscope" "CONFIG += kscope" kscope-ng.pro && (make -f Makefile.qscintilla all clean &) && (make -f Makefile.kscope all clean &) && rm Makefile.qscintilla Makefile.kscope
