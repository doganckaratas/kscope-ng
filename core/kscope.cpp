/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file kscope.cpp
 */


#include <QMessageBox>
#include <QTabWidget>
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>
#include <QDirIterator>
#include <QStandardItem>

#include "kscope.h"
#include "view.h"
#include "ui_mainwindow.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qsciscintillabase.h"
#include "Qsci/qscilexer.h"
#include "Qsci/qscilexerpython.h"
#include "Qsci/qscilexercpp.h"
#include "Qsci/qscilexermakefile.h"

//#include "events.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

/** === Roadmap ===
 *  @todo Implement Event.cpp, Action.cpp, View.cpp
 *  @todo Actually, Events.cpp must be abstract and inherited by EditorEvents.cpp and WindowEvents.cpp
 *  @todo Also Action.cpp must be same as Events classes
 *  @todo View.cpp needs to be setup all UI elements, in another thread.
 *  @todo Add Dynamic Line Numbering
 *  @todo Add Custom highlighters
 *  @todo Run QScintilla component and its' instances in another thread
 *  [OK] @todo Add Find&Replace
 *  [OK] @todo Add CScope wrapper
 *  @todo Refactor marked methods
 *  @todo Delete View XML and implement them with C++ (same with #4)
 *  @todo Fix Windows release
 *  @todo We need a cool and sleek icon :o
 */


KScope::KScope(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fr = new FindReplace(this);
    cs = new CScope(this);
    fr2 = new FindReplace2(this);

    KScope::setWindowTitle(QString::fromStdString("KScope-NG ") +
                               QString::fromStdString(VERSION));
    /*
     *  remove above line from production release
     */
    setupSignals();
    setIconStates(false);
}

void KScope::setupSignals()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveFileAs()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutDialog()));
    connect(ui->actionToggleSymbols, SIGNAL(triggered()), this, SLOT(toggleSymbols()));
    connect(ui->actionToggleCscope, SIGNAL(triggered()), this, SLOT(toggleCscope()));
    connect(ui->actionToggleFiles, SIGNAL(triggered()), this, SLOT(toggleFiles()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(editorUndo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(editorRedo()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(editorCut()));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(editorCopy()));
    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT(editorFindDialog()));
    connect(ui->actionReplace, SIGNAL(triggered()), this, SLOT(editorReplaceDialog()));
    connect(ui->actionReferences, SIGNAL(triggered()), this, SLOT(cscopeReferencesDialog()));
    connect(ui->actionDefinition, SIGNAL(triggered()), this, SLOT(cscopeDefinitionsDialog()));
    connect(ui->actionCalled_Functions, SIGNAL(triggered()), this, SLOT(cscopeCalledFunctionsDialog()));
    connect(ui->actionCalling_Functions, SIGNAL(triggered()), this, SLOT(cscopeCallingFunctionsDialog()));
    connect(ui->actionFind_Text, SIGNAL(triggered()), this, SLOT(cscopeFindTextDialog()));
    connect(ui->actionFind_EGrep_Pattern, SIGNAL(triggered()), this, SLOT(cscopeFindEGrepDialog()));
    connect(ui->actionFind_File, SIGNAL(triggered()), this, SLOT(cscopeFindFileDialog()));
    connect(ui->actionIncluding_Files, SIGNAL(triggered()), this, SLOT(cscopeIncludingFilesDialog()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(editorTabChanged(int)));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    connect(fr, SIGNAL(findRequest(QString, bool, bool, bool, bool)), this, SLOT(editorFindResponse(QString, bool, bool, bool, bool)));
    connect(fr, SIGNAL(replaceRequest(QString, QString, bool, bool, bool, bool, bool)), this, SLOT(editorReplaceResponse(QString,QString,bool, bool, bool, bool, bool)));
    connect(cs, SIGNAL(cscopeRequest(int,QString)), this, SLOT(cscopeResponse(int, QString)));

    /*
     * TODO: set up all action handlers
     */
}

void KScope::setIconStates(bool state)
{
    /*
     * TODO: not all actions needed to be enabled. arrange it
     */
    if (state == false) {
        ui->actionClose->setEnabled(false);
        ui->actionSave->setEnabled(false);
        ui->actionSave_All->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
        ui->actionSelect_All->setEnabled(false);
        ui->actionCut->setEnabled(false);
        ui->actionCopy->setEnabled(false);
        ui->actionCopy_As_HTML->setEnabled(false);
        ui->actionPaste->setEnabled(false);
        ui->actionPrint->setEnabled(false);
        ui->actionUndo->setEnabled(false);
        ui->actionRedo->setEnabled(false);
        ui->actionDeselect->setEnabled(false);
        ui->actionBlock_Selection->setEnabled(false);
        ui->actionOverwrite_Mode->setEnabled(false);
        ui->actionReload->setEnabled(false);
        ui->actionExport_as_HTML->setEnabled(false);
        ui->actionFind->setEnabled(false);
        ui->actionFind_Next->setEnabled(false);
        ui->actionFind_Previous->setEnabled(false);
        ui->actionReplace->setEnabled(false);
        ui->actionEnlarge_Font->setEnabled(false);
        ui->actionShrink_Font->setEnabled(false);
    } else {
        ui->actionClose->setEnabled(true);
        ui->actionSave_All->setEnabled(true);
        ui->actionSave_As->setEnabled(true);
        ui->actionSelect_All->setEnabled(true);
        ui->actionPaste->setEnabled(true);
        ui->actionPrint->setEnabled(true);
        ui->actionDeselect->setEnabled(true);
        ui->actionBlock_Selection->setEnabled(true);
        ui->actionOverwrite_Mode->setEnabled(true);
        ui->actionReload->setEnabled(true);
        ui->actionExport_as_HTML->setEnabled(true);
        ui->actionFind->setEnabled(true);
        ui->actionFind_Next->setEnabled(true);
        ui->actionFind_Previous->setEnabled(true);
        ui->actionReplace->setEnabled(true);
        ui->actionEnlarge_Font->setEnabled(true);
        ui->actionShrink_Font->setEnabled(true);
    }
}

void KScope::newFile()
{
    /* TODO: Refactor this method */

    QTabWidget *qtw = new QTabWidget(this);
    QHBoxLayout *qhbl = new QHBoxLayout(qtw);
    QsciScintilla *qsc = new QsciScintilla();
    qsc->setObjectName("editor");
    qsc->setMarginsFont(QFont("Ubuntu Mono", 11, QFont::Normal, false));
    qsc->setMarginLineNumbers(0,true);
    qsc->setMarginType(0, QsciScintilla::NumberMargin);
    qsc->setMarginWidth(0, "0000");
    qsc->setMarginsForegroundColor(QColor("#ff888888"));
    qtw->setTabText(qtw->indexOf(qtw), "New File");
    qtw->setDocumentMode(true);
    qtw->setObjectName("tab");
    connect(qsc, SIGNAL(selectionChanged()), this, SLOT(editorSelection()));
    connect(qsc, SIGNAL(textChanged()), this, SLOT(editorUpdate()));
    connect(qsc, SIGNAL(modificationChanged(bool)), this, SLOT(editorModified(bool)));
    connect(qsc, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(qsc, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
    connect(ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(editorPaste()));
    qhbl->addWidget(qsc);
    qhbl->setMargin(0);
    ui->tabWidget->addTab(qtw, QString::fromStdString("New File"));
    ui->tabWidget->setCurrentWidget(qtw);
    ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon(":/icons/icons/c_source.png"));
    ui->actionSave->setEnabled(false);
    ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(),"New File");
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->SendScintilla(QsciScintillaBase::SCI_SETSAVEPOINT,0);
    qsc->setFocus();
    setIconStates(true);
    D("New File");
}

void KScope::openFile()
{
    /* TODO: Refactor this method */
    QString fname = QFileDialog::getOpenFileName(this,
                                                 "Open File", "",
                                                 "All Files (*);;"
                                                 "Text File (*.txt);;"
                                                 "Makefile (Makefile);;"
                                                 "C File (*.c *.h);;"
                                                 "C++ File (*.cpp *.h)");
    if (fname != "") {
        QFile f(fname);
        if (f.open((QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite))) {
            KScope::newFile();
            QTextStream stream(&f);
            QFileInfo finfo(f);
            //qsc->setLexer(new QsciLexerCPP(this));
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->setFocus();
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(),fname);
            ui->tabWidget->setObjectName(fname);
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->setText(stream.readAll());
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->setModified(false);
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->SendScintilla(QsciScintillaBase::SCI_SETSAVEPOINT,0);
            /* Newline should be selectable from users,
             * which should has three options
             * -> Unix (\n)
             * -> Windows (\r\n)
             * -> Classic MacOS (\r)
             */

            // get recursive file list [Another Thread]
            KScope::getFiles(finfo.absolutePath());

            // setup cscope frontend [Another Thread]
            KScope::cscopeSetup("./cscope.out");

            // lexer | fix this !


            if (finfo.suffix() == "cpp" || finfo.suffix() == "c" || finfo.suffix() == "h" || finfo.suffix() == "hpp") {
                setupLexer(LEXER_CPP);
            } else if (finfo.suffix() == "py") {
                QsciLexerPython *qlpy = new QsciLexerPython(this);
                //qlpy->setFont(norm_font);
                ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->setLexer(qlpy);
            } else if (finfo.baseName() == "Makefile") {
                QsciLexerMakefile *qlmk = new QsciLexerMakefile(this);
                //qlmk->setFont(norm_font);
                ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->setLexer(qlmk);
            } else {
                //text document
                //ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->setFont(norm_font);
            }

        }
    }

    D("Open File");
}

void KScope::saveFile()
{
    /* TODO: Merge with Save As */

    if (ui->tabWidget->tabToolTip(ui->tabWidget->currentIndex()) != QString::fromStdString("New File")) {
        QFile f(ui->tabWidget->tabToolTip(ui->tabWidget->currentIndex()));
        if (f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
            QTextStream stream(&f);
            QFileInfo finfo(f);
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            stream << ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->text();
            f.close();
            ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon(":/icons/icons/c_source.png"));
            // reload document
            connect(ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor"), SIGNAL(selectionChanged()), this, SLOT(editorSelection()));
            connect(ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor"), SIGNAL(textChanged()), this, SLOT(editorUpdate()));
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->SendScintilla(QsciScintillaBase::SCI_SETSAVEPOINT,0);
            D("Save File");
        }
    } else {
        D("Save File As Triggered");
        this->saveFileAs();
    }

}

void KScope::saveFileAs()
{
    /* TODO: Refactor this method */

    D("Save File As");
    QString fname = QFileDialog::getSaveFileName(this,
                                                    "Save File As", "",
                                                    "All Files (*);;"
                                                    "Text File (*.txt);;"
                                                    "Makefile (Makefile);;"
                                                    "C File (*.c *.h);;"
                                                    "C++ File (*.cpp *.h)");
    if (fname != "")
    {
        QFile f(fname);
        if (f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
            QTextStream stream(&f);
            QFileInfo finfo(f);
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            stream << ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->text();
            f.close();
            ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(),fname);
            ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon(":/icons/icons/c_source.png"));
            // at this point reload document to track new changes
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->SendScintilla(QsciScintillaBase::SCI_SETSAVEPOINT,0);
        }
    } else {
        D("Save Canceled.");
    }
}

void KScope::closeFile(const int& index)
{
    // fix this and the other close routine
    // add close app event, cycle all modified inst's.
    QMessageBox qm;
    if (ui->tabWidget->widget(index)->findChild<QsciScintilla *>("editor")->SendScintilla(QsciScintillaBase::SCI_GETMODIFY)) {
        // if file was changed, focus to the file, otherwise silently close file
        ui->tabWidget->setCurrentIndex(index);
        if(qm.isHidden()) {
            qm.setWindowTitle("Confirm Close");
            qm.setIcon(QMessageBox::Question);
            qm.setWindowModality(Qt::WindowModal);
            qm.setText("File has been changed since last save.");
            qm.setInformativeText("Do you want to save it?");
            qm.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            qm.setDefaultButton(QMessageBox::Save);
            int ret = qm.exec();
            if (ret == QMessageBox::Save) {
                D("Save Clicked");
                KScope::saveFile();
            }
            if (ret == QMessageBox::Discard) {
                D("Discard Clicked");
                if (index == -1) {
                    return;
                }
                ui->tabWidget->widget(index)->findChild<QsciScintilla *>("editor")->close();
                ui->tabWidget->widget(index)->findChild<QsciScintilla *>("editor")->deleteLater();
                ui->tabWidget->widget(index)->deleteLater();
                /*
                 * MEMORY LEAK, delete tab content  & document too. [DONE]
                 */
                if (ui->tabWidget->count() <= 1) {
                    setIconStates(false);
                }
            }
            if (ret == QMessageBox::Cancel) {
                D("Cancel Clicked");
            }
        }
    } else {
        D("Close Tab File");

        if (index == -1) {
            return;
        }
        ui->tabWidget->widget(index)->findChild<QsciScintilla *>("editor")->close();
        ui->tabWidget->widget(index)->findChild<QsciScintilla *>("editor")->deleteLater();
        ui->tabWidget->widget(index)->deleteLater();
        /*
         * MEMORY LEAK, delete tab content  & document too. [DONE]
         */
        if (ui->tabWidget->count() <= 1) {
            setIconStates(false);
        }
    }
}

void KScope::closeFile()
{
    D("Close Current File");
    KScope::cscopeClear();
    KScope::closeFile(ui->tabWidget->currentIndex());
}

void KScope::getFiles(QString files)
{
    /* TODO: It missing first file, fix it. */
    ui->treeFiles->clear();
    QList<QTreeWidgetItem *> items;
    QTreeWidgetItem *itm;
    QDirIterator dir(files,QDirIterator::Subdirectories);
    while (dir.hasNext()) {
        QFile f(dir.next());
        if (QFileInfo(f).isFile()) {
            if (QFileInfo(f).suffix() == "c") {
                itm = new QTreeWidgetItem(0);
                itm->setText(0, "c");
                itm->setText(1, QFileInfo(f).fileName());
                items.append(itm);
            } else if (QFileInfo(f).suffix() == "h") {
                itm = new QTreeWidgetItem(0);
                itm->setText(0, "h");
                itm->setText(1, QFileInfo(f).fileName());
                items.append(itm);
            } else if (QFileInfo(f).suffix() == "cpp") {
                itm = new QTreeWidgetItem(0);
                itm->setText(0, "cpp");
                itm->setText(1, QFileInfo(f).fileName());
                items.append(itm);
            } else {
                ;
            }
        } else {
            ;
        }
    }
    ui->treeFiles->addTopLevelItems(items);
    //delete itm;
}

void KScope::cscopeSetup(QString path)
{
    cscope_bin = "cscope";
    //cscope_bin = "/Users/dogan/Desktop/kscope-ng-2/cscope/cscope";
    system((cscope_bin.toLatin1() + " -b -k -R -s " + path.toLatin1()).data());
}

void KScope::cscopeQuery(int mode, QString keyword)
{
    FILE *fd;
    char *tmp;
    char out[1023];
    int i,x;
    QList<QTreeWidgetItem *> items;
    QTreeWidgetItem *itm = nullptr;
    ui->treeResults->clear();
    fd = popen((cscope_bin.toLatin1() + " -d -L" + QString::number(mode).toLatin1() + " " + keyword.toLatin1()).data(), "r");

    while (fgets(out, sizeof(out)-1, fd) != nullptr) {
            //printf("%s", out);
            itm = new QTreeWidgetItem(0);
            for(i=x=0; out[i]; ++i)
                if(!isspace(out[i]) || (i>0 && !isspace(out[i-1])))
                    out[x++] = out[i];
            out[x] = '\0';
            tmp = strtok(out, " ");
            if(tmp != nullptr) {
                //printf("File\t: %s\n", tmp);
                itm->setText(0,QString(tmp));
            }
            tmp = strtok(NULL, " ");
            if(tmp != nullptr) {
                //printf("Func\t: %s\n", tmp);
                itm->setText(1,QString(tmp));
            }
            tmp = strtok(NULL, " ");
            if (tmp != nullptr) {
                //printf("Line\t: %s\n", tmp);
                itm->setText(2,QString(tmp));
            }
            tmp = strtok(NULL, "\n");
            if (tmp != nullptr) {
                //printf("Code\t: %s\n", tmp);
                itm->setText(3,QString(tmp));
            }
            items.append(itm);
            //printf("\n");
        }
    ui->treeResults->addTopLevelItems(items);
    pclose(fd);
    delete itm;
}

void KScope::cscopeClear()
{
    ui->treeResults->clear();
    ui->treeFiles->clear();
}

void KScope::cscopeDestroy()
{
    remove("cscope.out");
}

void KScope::setupLexer(enum LexerType l)
{
    QFont norm_font = QFont("Ubuntu Mono", 11, QFont::Normal, false);
    QFont ital_font = QFont("Ubuntu Mono", 11, QFont::Normal, true);
    QFont bold_font = QFont("Ubuntu Mono", 11, QFont::Bold, false);

    switch (l) {
        case LEXER_DEFAULT: {
            break;
        }
        case LEXER_CPP: {
            QsciLexerCPP cpp;
            /* colors: default black */
            cpp.setFont(norm_font); // global font
            cpp.setColor(QColor(128,128,128), QsciLexerCPP::Comment);
            cpp.setColor(QColor(128,128,128), QsciLexerCPP::CommentLine);
            cpp.setColor(QColor(0,0,255), QsciLexerCPP::CommentDoc);
            cpp.setColor(QColor(0,0,255), QsciLexerCPP::CommentLineDoc);
            cpp.setColor(QColor(202,96,202), QsciLexerCPP::CommentDocKeyword);
            cpp.setColor(QColor(221,0,0), QsciLexerCPP::DoubleQuotedString);
            cpp.setColor(QColor(255,0,255), QsciLexerCPP::SingleQuotedString);
            cpp.setColor(QColor(0,127,0), QsciLexerCPP::PreProcessor);
            cpp.setColor(QColor(127,0,0), QsciLexerCPP::KeywordSet2); //reserved words..
            cpp.setColor(QColor(0,0,0), QsciLexerCPP::Keyword); //struct etc..
            cpp.setColor(QColor(0,0,255), QsciLexerCPP::Number);
            cpp.setColor(QColor(0,0,0), QsciLexerCPP::Operator); // paranthesis
            cpp.setHighlightEscapeSequences(true);
            cpp.setColor(QColor(255,0,255), QsciLexerCPP::EscapeSequence);
            /* fonts : default norm_font */
            cpp.setFont(ital_font, QsciLexerCPP::Comment);
            cpp.setFont(ital_font, QsciLexerCPP::CommentLine);
            cpp.setFont(ital_font, QsciLexerCPP::CommentDoc);
            cpp.setFont(ital_font, QsciLexerCPP::CommentLineDoc);
            cpp.setFont(bold_font, QsciLexerCPP::CommentDocKeyword);
            cpp.setFont(bold_font, QsciLexerCPP::Keyword);
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->setLexer(&cpp);
            break;
        }
        case LEXER_MAKEFILE: {
            break;
        }
        case LEXER_PYTHON: {
            break;
        }
        case LEXER_JAVA: {
            break;
        }
//        default: {
//            break;
//        }
    }
}

void KScope::cscopeReferencesDialog()
{
    cs->showReferences();
    D("CScope Find Text Dialog");
}

void KScope::cscopeDefinitionsDialog()
{
    cs->showDefinitions();
    D("CScope Find Text Dialog");
}

void KScope::cscopeCalledFunctionsDialog()
{
    cs->showCalledFunctions();
    D("CScope Find Text Dialog");
}

void KScope::cscopeCallingFunctionsDialog()
{
    cs->showCallingFunctions();
    D("CScope Find Text Dialog");
}

void KScope::cscopeFindTextDialog()
{
    cs->showFindText();
    D("CScope Find Text Dialog");
}

void KScope::cscopeFindEGrepDialog()
{
    cs->showFindEGrep();
    D("CScope Find Text Dialog");
}

void KScope::cscopeFindFileDialog()
{
    cs->showFindFile();
    D("CScope Find Text Dialog");
}

void KScope::cscopeIncludingFilesDialog()
{
    cs->showIncludingFiles();
    D("CScope Find Text Dialog");
}

void KScope::cscopeResponse(int mode, QString keyword)
{
    cscopeQuery(mode, keyword);
}

void KScope::editorFindDialog()
{
    fr->showFind();
    fr2->show();
    D("Find Dialog");
}

void KScope::editorReplaceDialog()
{
    fr->showReplace();
    D("Replace Dialog");
}

void KScope::editorFindResponse(QString string, bool re, bool cs, bool wo, bool wr)
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->findFirst(string, re, cs, wo, wr);
}

void KScope::editorReplaceResponse(QString from, QString to, bool re, bool cs, bool wo, bool wr, bool all)
{
    if (!all) {
        if (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->findFirst(from, re, cs, wo, wr))
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->replace(to);
    } else {
        while (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->findFirst(from, re, cs, wo, wr))
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->replace(to);
    }
}

void KScope::editorTabChanged(int index)
{
     D("Tab Changed to " + QString::number(index).toStdString());
}

void KScope::editorUpdate()
{
    if (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->isUndoAvailable()) {
    // ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), "*" + ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
       /* TODO
        * Implement this correctly later
        */
        ui->actionUndo->setEnabled(true);
    } else {
        ui->actionUndo->setEnabled(false);
    }

    if (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->isRedoAvailable()) {
        ui->actionRedo->setEnabled(true);
    } else {
        ui->actionRedo->setEnabled(false);
    }
    D("Updated Text");
}

void KScope::editorModified(bool status)
{
    // there are some problems in here!!
    if (status == true) { // Icon change & show save prompt
        ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon(":/icons/icons/save.png"));
        ui->actionSave->setEnabled(true);
    } else {
        ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon(":/icons/icons/c_source.png"));
        ui->actionSave->setEnabled(false);
    }
}

void KScope::editorSelection()
{
    if (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->selectedText().length() > 0) {
        D("Selected Text");
    } else {
        D("Deselected Text");
    }
}

void KScope::editorUndo()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->undo();
    D("Undo");
}

void KScope::editorRedo()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->redo();
    D("Redo");
}

void KScope::editorCut()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->cut();
    if (! ui->actionPaste->isEnabled()) {
        ui->actionPaste->setEnabled(true);
    }
    D("Cut");
}

void KScope::editorCopy()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->copy();
    if (! ui->actionPaste->isEnabled()) {
        ui->actionPaste->setEnabled(true);
    }
    D("Copy");
}

void KScope::editorPaste()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->paste();
}

void KScope::toggleSymbols()
{
    if(ui->dockSymbols->isVisible() == true)
        ui->dockSymbols->close();
    else
        ui->dockSymbols->show();
}

void KScope::toggleCscope()
{
    if(ui->dockCscope->isVisible() == true)
        ui->dockCscope->close();
    else
        ui->dockCscope->show();
}

void KScope::toggleFiles()
{
    if(ui->dockFiles->isVisible() == true)
        ui->dockFiles->close();
    else
        ui->dockFiles->show();
}

void KScope::aboutDialog()
{
    QMessageBox *qm = new QMessageBox(this);
    qm->setMinimumHeight(60);
    qm->setWindowTitle("About");
    qm->setText("KScope-NG\n"
                "Qt Based CScope Frontend/IDE\n"
                "Written from scratch\n\n"
                "Version: "
                 VER_STR
                "Author: Dogan C. Karatas\n"
                "Release Date: "
                 RELEASE_DATE);
    qm->setDetailedText("Extra Info Goes Here.");
    qm->setWindowTitle("About KScope-NG");
    qm->exec();
}

int KScope::getFirstTabIdFromName(QTabWidget *qtw, std::string name)
{
    for(int i = 0; i < qtw->count(); i++) {
        if(name == qtw->tabText(i).toStdString()) {
            return i;
        }
    }
    return -1;
}


KScope::~KScope()
{
    cscopeDestroy();
    delete fr;
    delete ui;
}
