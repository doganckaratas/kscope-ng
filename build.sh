#!/bin/bash

qmake -makefile -o "Makefile.qscintilla" "CONFIG += qscintilla" src/editor/qscintilla.pri
sleep 1;
qmake -makefile -o "Makefile.kscope" "CONFIG += kscope" kscope-ng.pro
sleep 1;

make -f Makefile.qscintilla all clean &
make -f Makefile.kscope all clean &

rm Makefile.qscintilla Makefile.kscope
