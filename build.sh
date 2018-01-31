#!/bin/bash

qmake -makefile -o Makefile.qscintilla "CONFIG += qscintilla" kscope-ng.pro
qmake -makefile -o Makefile.kscope "CONFIG += kscope" kscope-ng.pro
if [ -e Makefile.qscintilla ] then; 
	make -f Makefile.qscintilla all clean &
fi

if [ -e Makefile.kscope ] then;
	make -f Makefile.kscope all clean &
fi
rm Makefile.qscintilla Makefile.kscope
