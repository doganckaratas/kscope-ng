# The project file for the QScintilla library.
#
# Copyright (c) 2017 Riverbank Computing Limited <info@riverbankcomputing.com>
# 
# This file is part of QScintilla.
# 
# This file may be used under the terms of the GNU General Public License
# version 3.0 as published by the Free Software Foundation and appearing in
# the file LICENSE included in the packaging of this file.  Please review the
# following information to ensure the GNU General Public License version 3.0
# requirements will be met: http://www.gnu.org/copyleft/gpl.html.
# 
# If you do not wish to use this file under the terms of the GPL version 3.0
# then you may purchase a commercial license.  For more information contact
# info@riverbankcomputing.com.
# 
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


# This must be kept in sync with Python/configure.py, Python/configure-old.py,
# example-Qt4Qt5/application.pro and designer-Qt4Qt5/designer.pro.
!win32:VERSION = 13.1.0

TEMPLATE = lib
CONFIG += qt warn_off thread exceptions hide_symbols

CONFIG(debug, debug|release) {
    mac: {
        TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}_debug
    } else {
        win32: {
            TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}d
        } else {
            TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}
        }
    }
} else {
    TARGET = qscintilla2_qt$${QT_MAJOR_VERSION}
}

INCLUDEPATH += ./qscintilla ./include ./lexlib ./src

!CONFIG(staticlib) {
    DEFINES += QSCINTILLA_MAKE_DLL
}
DEFINES += SCINTILLA_QT SCI_LEXER

greaterThan(QT_MAJOR_VERSION, 4) {
	QT += widgets printsupport

    greaterThan(QT_MINOR_VERSION, 1) {
	    macx:QT += macextras
    }

    # Work around QTBUG-39300.
    CONFIG -= android_install
}

greaterThan(QT_MAJOR_VERSION, 4) {

CONFIG += c++11
} else {
# For old versions of Qt

QMAKE_CXXFLAGS += -std=c++11 
}


# Comment this in if you want the internal Scintilla classes to be placed in a
# Scintilla namespace rather than pollute the global namespace.
#DEFINES += SCI_NAMESPACE

target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target

header.path = $$[QT_INSTALL_HEADERS]
header.files = Qsci
INSTALLS += header

trans.path = $$[QT_INSTALL_TRANSLATIONS]
trans.files = qscintilla_*.qm
INSTALLS += trans

qsci.path = $$[QT_INSTALL_DATA]
qsci.files = ./qsci
INSTALLS += qsci

greaterThan(QT_MAJOR_VERSION, 4) {
    features.path = $$[QT_HOST_DATA]/mkspecs/features
} else {
    features.path = $$[QT_INSTALL_DATA]/mkspecs/features
}
CONFIG(staticlib) {
    features.files = $$PWD/features_staticlib/qscintilla2.prf
} else {
    features.files = $$PWD/features/qscintilla2.prf
}
INSTALLS += features

HEADERS = \
        ./qscintilla/Qsci/qsciglobal.h \
        ./qscintilla/Qsci/qsciscintilla.h \
        ./qscintilla/Qsci/qsciscintillabase.h \
        ./qscintilla/Qsci/qsciabstractapis.h \
        ./qscintilla/Qsci/qsciapis.h \
        ./qscintilla/Qsci/qscicommand.h \
        ./qscintilla/Qsci/qscicommandset.h \
        ./qscintilla/Qsci/qscidocument.h \
        ./qscintilla/Qsci/qscilexer.h \
        ./qscintilla/Qsci/qscilexeravs.h \
        ./qscintilla/Qsci/qscilexerbash.h \
        ./qscintilla/Qsci/qscilexerbatch.h \
        ./qscintilla/Qsci/qscilexercmake.h \
        ./qscintilla/Qsci/qscilexercoffeescript.h \
        ./qscintilla/Qsci/qscilexercpp.h \
        ./qscintilla/Qsci/qscilexercsharp.h \
        ./qscintilla/Qsci/qscilexercss.h \
        ./qscintilla/Qsci/qscilexercustom.h \
        ./qscintilla/Qsci/qscilexerd.h \
        ./qscintilla/Qsci/qscilexerdiff.h \
        ./qscintilla/Qsci/qscilexerfortran.h \
        ./qscintilla/Qsci/qscilexerfortran77.h \
        ./qscintilla/Qsci/qscilexerhtml.h \
        ./qscintilla/Qsci/qscilexeridl.h \
        ./qscintilla/Qsci/qscilexerjava.h \
        ./qscintilla/Qsci/qscilexerjavascript.h \
        ./qscintilla/Qsci/qscilexerjson.h \
        ./qscintilla/Qsci/qscilexerlua.h \
        ./qscintilla/Qsci/qscilexermakefile.h \
        ./qscintilla/Qsci/qscilexermarkdown.h \
        ./qscintilla/Qsci/qscilexermatlab.h \
        ./qscintilla/Qsci/qscilexeroctave.h \
        ./qscintilla/Qsci/qscilexerpascal.h \
        ./qscintilla/Qsci/qscilexerperl.h \
        ./qscintilla/Qsci/qscilexerpostscript.h \
        ./qscintilla/Qsci/qscilexerpo.h \
        ./qscintilla/Qsci/qscilexerpov.h \
        ./qscintilla/Qsci/qscilexerproperties.h \
        ./qscintilla/Qsci/qscilexerpython.h \
        ./qscintilla/Qsci/qscilexerruby.h \
        ./qscintilla/Qsci/qscilexerspice.h \
        ./qscintilla/Qsci/qscilexersql.h \
        ./qscintilla/Qsci/qscilexertcl.h \
        ./qscintilla/Qsci/qscilexertex.h \
        ./qscintilla/Qsci/qscilexerverilog.h \
        ./qscintilla/Qsci/qscilexervhdl.h \
        ./qscintilla/Qsci/qscilexerxml.h \
        ./qscintilla/Qsci/qscilexeryaml.h \
        ./qscintilla/Qsci/qscimacro.h \
        ./qscintilla/Qsci/qsciprinter.h \
        ./qscintilla/Qsci/qscistyle.h \
        ./qscintilla/Qsci/qscistyledtext.h \
        ./qscintilla/ListBoxQt.h \
        ./qscintilla/SciClasses.h \
        ./qscintilla/SciNamespace.h \
        ./qscintilla/ScintillaQt.h \
        ./include/ILexer.h \
        ./include/Platform.h \
        ./include/Sci_Position.h \
        ./include/SciLexer.h \
        ./include/Scintilla.h \
        ./include/ScintillaWidget.h \
        ./lexlib/Accessor.h \
        ./lexlib/CharacterCategory.h \
        ./lexlib/CharacterSet.h \
        ./lexlib/LexAccessor.h \
        ./lexlib/LexerBase.h \
        ./lexlib/LexerModule.h \
        ./lexlib/LexerNoExceptions.h \
        ./lexlib/LexerSimple.h \
        ./lexlib/OptionSet.h \
        ./lexlib/PropSetSimple.h \
        ./lexlib/StringCopy.h \
        ./lexlib/StyleContext.h \
        ./lexlib/SubStyles.h \
        ./lexlib/WordList.h \
        ./src/AutoComplete.h \
        ./src/CallTip.h \
        ./src/CaseConvert.h \
        ./src/CaseFolder.h \
        ./src/Catalogue.h \
        ./src/CellBuffer.h \
        ./src/CharClassify.h \
        ./src/ContractionState.h \
        ./src/Decoration.h \
        ./src/Document.h \
        ./src/EditModel.h \
        ./src/Editor.h \
        ./src/EditView.h \
        ./src/ExternalLexer.h \
        ./src/FontQuality.h \
        ./src/Indicator.h \
        ./src/KeyMap.h \
        ./src/LineMarker.h \
        ./src/MarginView.h \
        ./src/Partitioning.h \
        ./src/PerLine.h \
        ./src/PositionCache.h \
        ./src/RESearch.h \
        ./src/RunStyles.h \
        ./src/ScintillaBase.h \
        ./src/Selection.h \
        ./src/SplitVector.h \
        ./src/Style.h \
        ./src/UnicodeFromUTF8.h \
        ./src/UniConversion.h \
        ./src/ViewStyle.h \
        ./src/XPM.h

SOURCES = \
        ./qscintilla/qsciscintilla.cpp \
        ./qscintilla/qsciscintillabase.cpp \
        ./qscintilla/qsciabstractapis.cpp \
        ./qscintilla/qsciapis.cpp \
        ./qscintilla/qscicommand.cpp \
        ./qscintilla/qscicommandset.cpp \
        ./qscintilla/qscidocument.cpp \
        ./qscintilla/qscilexer.cpp \
        ./qscintilla/qscilexeravs.cpp \
        ./qscintilla/qscilexerbash.cpp \
        ./qscintilla/qscilexerbatch.cpp \
        ./qscintilla/qscilexercmake.cpp \
        ./qscintilla/qscilexercoffeescript.cpp \
        ./qscintilla/qscilexercpp.cpp \
        ./qscintilla/qscilexercsharp.cpp \
        ./qscintilla/qscilexercss.cpp \
        ./qscintilla/qscilexercustom.cpp \
        ./qscintilla/qscilexerd.cpp \
        ./qscintilla/qscilexerdiff.cpp \
        ./qscintilla/qscilexerfortran.cpp \
        ./qscintilla/qscilexerfortran77.cpp \
        ./qscintilla/qscilexerhtml.cpp \
        ./qscintilla/qscilexeridl.cpp \
        ./qscintilla/qscilexerjava.cpp \
        ./qscintilla/qscilexerjavascript.cpp \
        ./qscintilla/qscilexerjson.cpp \
        ./qscintilla/qscilexerlua.cpp \
        ./qscintilla/qscilexermakefile.cpp \
        ./qscintilla/qscilexermarkdown.cpp \
        ./qscintilla/qscilexermatlab.cpp \
        ./qscintilla/qscilexeroctave.cpp \
        ./qscintilla/qscilexerpascal.cpp \
        ./qscintilla/qscilexerperl.cpp \
        ./qscintilla/qscilexerpostscript.cpp \
        ./qscintilla/qscilexerpo.cpp \
        ./qscintilla/qscilexerpov.cpp \
        ./qscintilla/qscilexerproperties.cpp \
        ./qscintilla/qscilexerpython.cpp \
        ./qscintilla/qscilexerruby.cpp \
        ./qscintilla/qscilexerspice.cpp \
        ./qscintilla/qscilexersql.cpp \
        ./qscintilla/qscilexertcl.cpp \
        ./qscintilla/qscilexertex.cpp \
        ./qscintilla/qscilexerverilog.cpp \
        ./qscintilla/qscilexervhdl.cpp \
        ./qscintilla/qscilexerxml.cpp \
        ./qscintilla/qscilexeryaml.cpp \
        ./qscintilla/qscimacro.cpp \
        ./qscintilla/qsciprinter.cpp \
        ./qscintilla/qscistyle.cpp \
        ./qscintilla/qscistyledtext.cpp \
    ./qscintilla/MacPasteboardMime.cpp \
    ./qscintilla/InputMethod.cpp \
        ./qscintilla/SciClasses.cpp \
        ./qscintilla/ListBoxQt.cpp \
        ./qscintilla/PlatQt.cpp \
        ./qscintilla/ScintillaQt.cpp \
        ./lexers/LexA68k.cpp \
        ./lexers/LexAbaqus.cpp \
        ./lexers/LexAda.cpp \
        ./lexers/LexAPDL.cpp \
        ./lexers/LexAsm.cpp \
        ./lexers/LexAsn1.cpp \
        ./lexers/LexASY.cpp \
        ./lexers/LexAU3.cpp \
        ./lexers/LexAVE.cpp \
        ./lexers/LexAVS.cpp \
        ./lexers/LexBaan.cpp \
        ./lexers/LexBash.cpp \
        ./lexers/LexBasic.cpp \
        ./lexers/LexBatch.cpp \
        ./lexers/LexBibTeX.cpp \
        ./lexers/LexBullant.cpp \
        ./lexers/LexCaml.cpp \
        ./lexers/LexCLW.cpp \
        ./lexers/LexCmake.cpp \
        ./lexers/LexCOBOL.cpp \
        ./lexers/LexCoffeeScript.cpp \
        ./lexers/LexConf.cpp \
        ./lexers/LexCPP.cpp \
        ./lexers/LexCrontab.cpp \
        ./lexers/LexCsound.cpp \
        ./lexers/LexCSS.cpp \
        ./lexers/LexD.cpp \
        ./lexers/LexDiff.cpp \
        ./lexers/LexDMAP.cpp \
        ./lexers/LexDMIS.cpp \
        ./lexers/LexECL.cpp \
        ./lexers/LexEDIFACT.cpp \
        ./lexers/LexEiffel.cpp \
        ./lexers/LexErlang.cpp \
        ./lexers/LexErrorList.cpp \
        ./lexers/LexEScript.cpp \
        ./lexers/LexFlagship.cpp \
        ./lexers/LexForth.cpp \
        ./lexers/LexFortran.cpp \
        ./lexers/LexGAP.cpp \
        ./lexers/LexGui4Cli.cpp \
        ./lexers/LexHaskell.cpp \
        ./lexers/LexHex.cpp \
        ./lexers/LexHTML.cpp \
        ./lexers/LexInno.cpp \
        ./lexers/LexJSON.cpp \
        ./lexers/LexKix.cpp \
        ./lexers/LexKVIrc.cpp \
        ./lexers/LexLaTeX.cpp \
        ./lexers/LexLisp.cpp \
        ./lexers/LexLout.cpp \
        ./lexers/LexLua.cpp \
        ./lexers/LexMagik.cpp \
        ./lexers/LexMake.cpp \
        ./lexers/LexMarkdown.cpp \
        ./lexers/LexMatlab.cpp \
        ./lexers/LexMetapost.cpp \
        ./lexers/LexMMIXAL.cpp \
        ./lexers/LexModula.cpp \
        ./lexers/LexMPT.cpp \
        ./lexers/LexMSSQL.cpp \
        ./lexers/LexMySQL.cpp \
        ./lexers/LexNimrod.cpp \
        ./lexers/LexNsis.cpp \
        ./lexers/LexNull.cpp \
        ./lexers/LexOpal.cpp \
        ./lexers/LexOScript.cpp \
        ./lexers/LexPascal.cpp \
        ./lexers/LexPB.cpp \
        ./lexers/LexPerl.cpp \
        ./lexers/LexPLM.cpp \
        ./lexers/LexPO.cpp \
        ./lexers/LexPOV.cpp \
        ./lexers/LexPowerPro.cpp \
        ./lexers/LexPowerShell.cpp \
        ./lexers/LexProgress.cpp \
        ./lexers/LexProps.cpp \
        ./lexers/LexPS.cpp \
        ./lexers/LexPython.cpp \
        ./lexers/LexR.cpp \
        ./lexers/LexRebol.cpp \
        ./lexers/LexRegistry.cpp \
        ./lexers/LexRuby.cpp \
        ./lexers/LexRust.cpp \
        ./lexers/LexScriptol.cpp \
        ./lexers/LexSmalltalk.cpp \
        ./lexers/LexSML.cpp \
        ./lexers/LexSorcus.cpp \
        ./lexers/LexSpecman.cpp \
        ./lexers/LexSpice.cpp \
        ./lexers/LexSQL.cpp \
        ./lexers/LexSTTXT.cpp \
        ./lexers/LexTACL.cpp \
        ./lexers/LexTADS3.cpp \
        ./lexers/LexTAL.cpp \
        ./lexers/LexTCL.cpp \
        ./lexers/LexTCMD.cpp \
        ./lexers/LexTeX.cpp \
        ./lexers/LexTxt2tags.cpp \
        ./lexers/LexVB.cpp \
        ./lexers/LexVerilog.cpp \
        ./lexers/LexVHDL.cpp \
        ./lexers/LexVisualProlog.cpp \
        ./lexers/LexYAML.cpp \
        ./lexlib/Accessor.cpp \
        ./lexlib/CharacterCategory.cpp \
        ./lexlib/CharacterSet.cpp \
        ./lexlib/LexerBase.cpp \
        ./lexlib/LexerModule.cpp \
        ./lexlib/LexerNoExceptions.cpp \
        ./lexlib/LexerSimple.cpp \
        ./lexlib/PropSetSimple.cpp \
        ./lexlib/StyleContext.cpp \
        ./lexlib/WordList.cpp \
        ./src/AutoComplete.cpp \
        ./src/CallTip.cpp \
        ./src/CaseConvert.cpp \
        ./src/CaseFolder.cpp \
        ./src/Catalogue.cpp \
        ./src/CellBuffer.cpp \
        ./src/CharClassify.cpp \
        ./src/ContractionState.cpp \
        ./src/Decoration.cpp \
        ./src/Document.cpp \
        ./src/EditModel.cpp \
        ./src/Editor.cpp \
        ./src/EditView.cpp \
        ./src/ExternalLexer.cpp \
        ./src/Indicator.cpp \
    ./src/KeyMap.cpp \
        ./src/LineMarker.cpp \
        ./src/MarginView.cpp \
        ./src/PerLine.cpp \
        ./src/PositionCache.cpp \
    ./src/RESearch.cpp \
        ./src/RunStyles.cpp \
    ./src/ScintillaBase.cpp \
    ./src/Selection.cpp \
        ./src/Style.cpp \
        ./src/UniConversion.cpp \
        ./src/ViewStyle.cpp \
        ./src/XPM.cpp

TRANSLATIONS = \
	qscintilla_cs.ts \
	qscintilla_de.ts \
	qscintilla_es.ts \
	qscintilla_fr.ts \
	qscintilla_pt_br.ts
