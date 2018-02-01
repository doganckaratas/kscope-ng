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
qscintilla {
!win32:VERSION = 13.1.0

TEMPLATE = lib
CONFIG += qt warn_off thread exceptions hide_symbols staticlib

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

INCLUDEPATH += ./src/editor/qscintilla ./src/editor/include ./src/editor/lexlib ./src/editor/src

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
qsci.files = ./src/editor/qsci
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
        ./src/editor/qscintilla/Qsci/qsciglobal.h \
        ./src/editor/qscintilla/Qsci/qsciscintilla.h \
        ./src/editor/qscintilla/Qsci/qsciscintillabase.h \
        ./src/editor/qscintilla/Qsci/qsciabstractapis.h \
        ./src/editor/qscintilla/Qsci/qsciapis.h \
        ./src/editor/qscintilla/Qsci/qscicommand.h \
        ./src/editor/qscintilla/Qsci/qscicommandset.h \
        ./src/editor/qscintilla/Qsci/qscidocument.h \
        ./src/editor/qscintilla/Qsci/qscilexer.h \
        ./src/editor/qscintilla/Qsci/qscilexeravs.h \
        ./src/editor/qscintilla/Qsci/qscilexerbash.h \
        ./src/editor/qscintilla/Qsci/qscilexerbatch.h \
        ./src/editor/qscintilla/Qsci/qscilexercmake.h \
        ./src/editor/qscintilla/Qsci/qscilexercoffeescript.h \
        ./src/editor/qscintilla/Qsci/qscilexercpp.h \
        ./src/editor/qscintilla/Qsci/qscilexercsharp.h \
        ./src/editor/qscintilla/Qsci/qscilexercss.h \
        ./src/editor/qscintilla/Qsci/qscilexercustom.h \
        ./src/editor/qscintilla/Qsci/qscilexerd.h \
        ./src/editor/qscintilla/Qsci/qscilexerdiff.h \
        ./src/editor/qscintilla/Qsci/qscilexerfortran.h \
        ./src/editor/qscintilla/Qsci/qscilexerfortran77.h \
        ./src/editor/qscintilla/Qsci/qscilexerhtml.h \
        ./src/editor/qscintilla/Qsci/qscilexeridl.h \
        ./src/editor/qscintilla/Qsci/qscilexerjava.h \
        ./src/editor/qscintilla/Qsci/qscilexerjavascript.h \
        ./src/editor/qscintilla/Qsci/qscilexerjson.h \
        ./src/editor/qscintilla/Qsci/qscilexerlua.h \
        ./src/editor/qscintilla/Qsci/qscilexermakefile.h \
        ./src/editor/qscintilla/Qsci/qscilexermarkdown.h \
        ./src/editor/qscintilla/Qsci/qscilexermatlab.h \
        ./src/editor/qscintilla/Qsci/qscilexeroctave.h \
        ./src/editor/qscintilla/Qsci/qscilexerpascal.h \
        ./src/editor/qscintilla/Qsci/qscilexerperl.h \
        ./src/editor/qscintilla/Qsci/qscilexerpostscript.h \
        ./src/editor/qscintilla/Qsci/qscilexerpo.h \
        ./src/editor/qscintilla/Qsci/qscilexerpov.h \
        ./src/editor/qscintilla/Qsci/qscilexerproperties.h \
        ./src/editor/qscintilla/Qsci/qscilexerpython.h \
        ./src/editor/qscintilla/Qsci/qscilexerruby.h \
        ./src/editor/qscintilla/Qsci/qscilexerspice.h \
        ./src/editor/qscintilla/Qsci/qscilexersql.h \
        ./src/editor/qscintilla/Qsci/qscilexertcl.h \
        ./src/editor/qscintilla/Qsci/qscilexertex.h \
        ./src/editor/qscintilla/Qsci/qscilexerverilog.h \
        ./src/editor/qscintilla/Qsci/qscilexervhdl.h \
        ./src/editor/qscintilla/Qsci/qscilexerxml.h \
        ./src/editor/qscintilla/Qsci/qscilexeryaml.h \
        ./src/editor/qscintilla/Qsci/qscimacro.h \
        ./src/editor/qscintilla/Qsci/qsciprinter.h \
        ./src/editor/qscintilla/Qsci/qscistyle.h \
        ./src/editor/qscintilla/Qsci/qscistyledtext.h \
        ./src/editor/qscintilla/ListBoxQt.h \
        ./src/editor/qscintilla/SciClasses.h \
        ./src/editor/qscintilla/SciNamespace.h \
        ./src/editor/qscintilla/ScintillaQt.h \
        ./src/editor/include/ILexer.h \
        ./src/editor/include/Platform.h \
        ./src/editor/include/Sci_Position.h \
        ./src/editor/include/SciLexer.h \
        ./src/editor/include/Scintilla.h \
        ./src/editor/include/ScintillaWidget.h \
        ./src/editor/lexlib/Accessor.h \
        ./src/editor/lexlib/CharacterCategory.h \
        ./src/editor/lexlib/CharacterSet.h \
        ./src/editor/lexlib/LexAccessor.h \
        ./src/editor/lexlib/LexerBase.h \
        ./src/editor/lexlib/LexerModule.h \
        ./src/editor/lexlib/LexerNoExceptions.h \
        ./src/editor/lexlib/LexerSimple.h \
        ./src/editor/lexlib/OptionSet.h \
        ./src/editor/lexlib/PropSetSimple.h \
        ./src/editor/lexlib/StringCopy.h \
        ./src/editor/lexlib/StyleContext.h \
        ./src/editor/lexlib/SubStyles.h \
        ./src/editor/lexlib/WordList.h \
        ./src/editor/src/AutoComplete.h \
        ./src/editor/src/CallTip.h \
        ./src/editor/src/CaseConvert.h \
        ./src/editor/src/CaseFolder.h \
        ./src/editor/src/Catalogue.h \
        ./src/editor/src/CellBuffer.h \
        ./src/editor/src/CharClassify.h \
        ./src/editor/src/ContractionState.h \
        ./src/editor/src/Decoration.h \
        ./src/editor/src/Document.h \
        ./src/editor/src/EditModel.h \
        ./src/editor/src/Editor.h \
        ./src/editor/src/EditView.h \
        ./src/editor/src/ExternalLexer.h \
        ./src/editor/src/FontQuality.h \
        ./src/editor/src/Indicator.h \
        ./src/editor/src/KeyMap.h \
        ./src/editor/src/LineMarker.h \
        ./src/editor/src/MarginView.h \
        ./src/editor/src/Partitioning.h \
        ./src/editor/src/PerLine.h \
        ./src/editor/src/PositionCache.h \
        ./src/editor/src/RESearch.h \
        ./src/editor/src/RunStyles.h \
        ./src/editor/src/ScintillaBase.h \
        ./src/editor/src/Selection.h \
        ./src/editor/src/SplitVector.h \
        ./src/editor/src/Style.h \
        ./src/editor/src/UnicodeFromUTF8.h \
        ./src/editor/src/UniConversion.h \
        ./src/editor/src/ViewStyle.h \
        ./src/editor/src/XPM.h

SOURCES = \
        ./src/editor/qscintilla/qsciscintilla.cpp \
        ./src/editor/qscintilla/qsciscintillabase.cpp \
        ./src/editor/qscintilla/qsciabstractapis.cpp \
        ./src/editor/qscintilla/qsciapis.cpp \
        ./src/editor/qscintilla/qscicommand.cpp \
        ./src/editor/qscintilla/qscicommandset.cpp \
        ./src/editor/qscintilla/qscidocument.cpp \
        ./src/editor/qscintilla/qscilexer.cpp \
        ./src/editor/qscintilla/qscilexeravs.cpp \
        ./src/editor/qscintilla/qscilexerbash.cpp \
        ./src/editor/qscintilla/qscilexerbatch.cpp \
        ./src/editor/qscintilla/qscilexercmake.cpp \
        ./src/editor/qscintilla/qscilexercoffeescript.cpp \
        ./src/editor/qscintilla/qscilexercpp.cpp \
        ./src/editor/qscintilla/qscilexercsharp.cpp \
        ./src/editor/qscintilla/qscilexercss.cpp \
        ./src/editor/qscintilla/qscilexercustom.cpp \
        ./src/editor/qscintilla/qscilexerd.cpp \
        ./src/editor/qscintilla/qscilexerdiff.cpp \
        ./src/editor/qscintilla/qscilexerfortran.cpp \
        ./src/editor/qscintilla/qscilexerfortran77.cpp \
        ./src/editor/qscintilla/qscilexerhtml.cpp \
        ./src/editor/qscintilla/qscilexeridl.cpp \
        ./src/editor/qscintilla/qscilexerjava.cpp \
        ./src/editor/qscintilla/qscilexerjavascript.cpp \
        ./src/editor/qscintilla/qscilexerjson.cpp \
        ./src/editor/qscintilla/qscilexerlua.cpp \
        ./src/editor/qscintilla/qscilexermakefile.cpp \
        ./src/editor/qscintilla/qscilexermarkdown.cpp \
        ./src/editor/qscintilla/qscilexermatlab.cpp \
        ./src/editor/qscintilla/qscilexeroctave.cpp \
        ./src/editor/qscintilla/qscilexerpascal.cpp \
        ./src/editor/qscintilla/qscilexerperl.cpp \
        ./src/editor/qscintilla/qscilexerpostscript.cpp \
        ./src/editor/qscintilla/qscilexerpo.cpp \
        ./src/editor/qscintilla/qscilexerpov.cpp \
        ./src/editor/qscintilla/qscilexerproperties.cpp \
        ./src/editor/qscintilla/qscilexerpython.cpp \
        ./src/editor/qscintilla/qscilexerruby.cpp \
        ./src/editor/qscintilla/qscilexerspice.cpp \
        ./src/editor/qscintilla/qscilexersql.cpp \
        ./src/editor/qscintilla/qscilexertcl.cpp \
        ./src/editor/qscintilla/qscilexertex.cpp \
        ./src/editor/qscintilla/qscilexerverilog.cpp \
        ./src/editor/qscintilla/qscilexervhdl.cpp \
        ./src/editor/qscintilla/qscilexerxml.cpp \
        ./src/editor/qscintilla/qscilexeryaml.cpp \
        ./src/editor/qscintilla/qscimacro.cpp \
        ./src/editor/qscintilla/qsciprinter.cpp \
        ./src/editor/qscintilla/qscistyle.cpp \
        ./src/editor/qscintilla/qscistyledtext.cpp \
    ./src/editor/qscintilla/MacPasteboardMime.cpp \
    ./src/editor/qscintilla/InputMethod.cpp \
        ./src/editor/qscintilla/SciClasses.cpp \
        ./src/editor/qscintilla/ListBoxQt.cpp \
        ./src/editor/qscintilla/PlatQt.cpp \
        ./src/editor/qscintilla/ScintillaQt.cpp \
        ./src/editor/lexers/LexA68k.cpp \
        ./src/editor/lexers/LexAbaqus.cpp \
        ./src/editor/lexers/LexAda.cpp \
        ./src/editor/lexers/LexAPDL.cpp \
        ./src/editor/lexers/LexAsm.cpp \
        ./src/editor/lexers/LexAsn1.cpp \
        ./src/editor/lexers/LexASY.cpp \
        ./src/editor/lexers/LexAU3.cpp \
        ./src/editor/lexers/LexAVE.cpp \
        ./src/editor/lexers/LexAVS.cpp \
        ./src/editor/lexers/LexBaan.cpp \
        ./src/editor/lexers/LexBash.cpp \
        ./src/editor/lexers/LexBasic.cpp \
        ./src/editor/lexers/LexBatch.cpp \
        ./src/editor/lexers/LexBibTeX.cpp \
        ./src/editor/lexers/LexBullant.cpp \
        ./src/editor/lexers/LexCaml.cpp \
        ./src/editor/lexers/LexCLW.cpp \
        ./src/editor/lexers/LexCmake.cpp \
        ./src/editor/lexers/LexCOBOL.cpp \
        ./src/editor/lexers/LexCoffeeScript.cpp \
        ./src/editor/lexers/LexConf.cpp \
        ./src/editor/lexers/LexCPP.cpp \
        ./src/editor/lexers/LexCrontab.cpp \
        ./src/editor/lexers/LexCsound.cpp \
        ./src/editor/lexers/LexCSS.cpp \
        ./src/editor/lexers/LexD.cpp \
        ./src/editor/lexers/LexDiff.cpp \
        ./src/editor/lexers/LexDMAP.cpp \
        ./src/editor/lexers/LexDMIS.cpp \
        ./src/editor/lexers/LexECL.cpp \
        ./src/editor/lexers/LexEDIFACT.cpp \
        ./src/editor/lexers/LexEiffel.cpp \
        ./src/editor/lexers/LexErlang.cpp \
        ./src/editor/lexers/LexErrorList.cpp \
        ./src/editor/lexers/LexEScript.cpp \
        ./src/editor/lexers/LexFlagship.cpp \
        ./src/editor/lexers/LexForth.cpp \
        ./src/editor/lexers/LexFortran.cpp \
        ./src/editor/lexers/LexGAP.cpp \
        ./src/editor/lexers/LexGui4Cli.cpp \
        ./src/editor/lexers/LexHaskell.cpp \
        ./src/editor/lexers/LexHex.cpp \
        ./src/editor/lexers/LexHTML.cpp \
        ./src/editor/lexers/LexInno.cpp \
        ./src/editor/lexers/LexJSON.cpp \
        ./src/editor/lexers/LexKix.cpp \
        ./src/editor/lexers/LexKVIrc.cpp \
        ./src/editor/lexers/LexLaTeX.cpp \
        ./src/editor/lexers/LexLisp.cpp \
        ./src/editor/lexers/LexLout.cpp \
        ./src/editor/lexers/LexLua.cpp \
        ./src/editor/lexers/LexMagik.cpp \
        ./src/editor/lexers/LexMake.cpp \
        ./src/editor/lexers/LexMarkdown.cpp \
        ./src/editor/lexers/LexMatlab.cpp \
        ./src/editor/lexers/LexMetapost.cpp \
        ./src/editor/lexers/LexMMIXAL.cpp \
        ./src/editor/lexers/LexModula.cpp \
        ./src/editor/lexers/LexMPT.cpp \
        ./src/editor/lexers/LexMSSQL.cpp \
        ./src/editor/lexers/LexMySQL.cpp \
        ./src/editor/lexers/LexNimrod.cpp \
        ./src/editor/lexers/LexNsis.cpp \
        ./src/editor/lexers/LexNull.cpp \
        ./src/editor/lexers/LexOpal.cpp \
        ./src/editor/lexers/LexOScript.cpp \
        ./src/editor/lexers/LexPascal.cpp \
        ./src/editor/lexers/LexPB.cpp \
        ./src/editor/lexers/LexPerl.cpp \
        ./src/editor/lexers/LexPLM.cpp \
        ./src/editor/lexers/LexPO.cpp \
        ./src/editor/lexers/LexPOV.cpp \
        ./src/editor/lexers/LexPowerPro.cpp \
        ./src/editor/lexers/LexPowerShell.cpp \
        ./src/editor/lexers/LexProgress.cpp \
        ./src/editor/lexers/LexProps.cpp \
        ./src/editor/lexers/LexPS.cpp \
        ./src/editor/lexers/LexPython.cpp \
        ./src/editor/lexers/LexR.cpp \
        ./src/editor/lexers/LexRebol.cpp \
        ./src/editor/lexers/LexRegistry.cpp \
        ./src/editor/lexers/LexRuby.cpp \
        ./src/editor/lexers/LexRust.cpp \
        ./src/editor/lexers/LexScriptol.cpp \
        ./src/editor/lexers/LexSmalltalk.cpp \
        ./src/editor/lexers/LexSML.cpp \
        ./src/editor/lexers/LexSorcus.cpp \
        ./src/editor/lexers/LexSpecman.cpp \
        ./src/editor/lexers/LexSpice.cpp \
        ./src/editor/lexers/LexSQL.cpp \
        ./src/editor/lexers/LexSTTXT.cpp \
        ./src/editor/lexers/LexTACL.cpp \
        ./src/editor/lexers/LexTADS3.cpp \
        ./src/editor/lexers/LexTAL.cpp \
        ./src/editor/lexers/LexTCL.cpp \
        ./src/editor/lexers/LexTCMD.cpp \
        ./src/editor/lexers/LexTeX.cpp \
        ./src/editor/lexers/LexTxt2tags.cpp \
        ./src/editor/lexers/LexVB.cpp \
        ./src/editor/lexers/LexVerilog.cpp \
        ./src/editor/lexers/LexVHDL.cpp \
        ./src/editor/lexers/LexVisualProlog.cpp \
        ./src/editor/lexers/LexYAML.cpp \
        ./src/editor/lexlib/Accessor.cpp \
        ./src/editor/lexlib/CharacterCategory.cpp \
        ./src/editor/lexlib/CharacterSet.cpp \
        ./src/editor/lexlib/LexerBase.cpp \
        ./src/editor/lexlib/LexerModule.cpp \
        ./src/editor/lexlib/LexerNoExceptions.cpp \
        ./src/editor/lexlib/LexerSimple.cpp \
        ./src/editor/lexlib/PropSetSimple.cpp \
        ./src/editor/lexlib/StyleContext.cpp \
        ./src/editor/lexlib/WordList.cpp \
        ./src/editor/src/AutoComplete.cpp \
        ./src/editor/src/CallTip.cpp \
        ./src/editor/src/CaseConvert.cpp \
        ./src/editor/src/CaseFolder.cpp \
        ./src/editor/src/Catalogue.cpp \
        ./src/editor/src/CellBuffer.cpp \
        ./src/editor/src/CharClassify.cpp \
        ./src/editor/src/ContractionState.cpp \
        ./src/editor/src/Decoration.cpp \
        ./src/editor/src/Document.cpp \
        ./src/editor/src/EditModel.cpp \
        ./src/editor/src/Editor.cpp \
        ./src/editor/src/EditView.cpp \
        ./src/editor/src/ExternalLexer.cpp \
        ./src/editor/src/Indicator.cpp \
        ./src/editor/src/KeyMap.cpp \
        ./src/editor/src/LineMarker.cpp \
        ./src/editor/src/MarginView.cpp \
        ./src/editor/src/PerLine.cpp \
        ./src/editor/src/PositionCache.cpp \
        ./src/editor/src/RESearch.cpp \
        ./src/editor/src/RunStyles.cpp \
        ./src/editor/src/ScintillaBase.cpp \
        ./src/editor/src/Selection.cpp \
        ./src/editor/src/Style.cpp \
        ./src/editor/src/UniConversion.cpp \
        ./src/editor/src/ViewStyle.cpp \
        ./src/editor/src/XPM.cpp

TRANSLATIONS = \
	qscintilla_cs.ts \
	qscintilla_de.ts \
	qscintilla_es.ts \
	qscintilla_fr.ts \
	qscintilla_pt_br.ts
}
