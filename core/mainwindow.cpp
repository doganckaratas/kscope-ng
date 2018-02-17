/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file mainwindow.cpp
 */


#include <QMessageBox>
#include <QTabWidget>
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Qsci/qsciscintilla.h"
#include "Qsci/qsciscintillabase.h"
#include "Qsci/qscilexer.h"
#include "Qsci/qscilexerpython.h"
#include "Qsci/qscilexercpp.h"
#include "Qsci/qscilexermakefile.h"

//#include "events.h"

#include <iostream>

/** === Roadmap ===
 *  @todo Implement Event.cpp, Action.cpp, View.cpp
 *  @todo Actually, Events.cpp must be abstract and inherited by EditorEvents.cpp and WindowEvents.cpp
 *  @todo Also Action.cpp must be same as Events classes
 *  @todo View.cpp needs to be setup all UI elements, in another thread.
 *  @todo Add Dynamic Line Numbering
 *  @todo Add Custom highlighters
 *  @todo Run QScintilla component and its' instances in another thread
 *  @todo Add Find&Replace
 *  @todo Add CScope wrapper
 *  @todo Refactor marked methods
 *  @todo Delete View XML and implement them with C++ (same with #4)
 *  @todo Fix Windows release
 *  @todo We need a cool and sleek icon :o
 */


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fr = new FindReplace(this);
    MainWindow::setWindowTitle(QString::fromStdString("KScope-NG ") +
                               QString::fromStdString(VERSION));
    /*
     *  remove above line from production release
     */
    setupSignals();
    setIconStates(false);
}

void MainWindow::setupSignals()
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
    connect(ui->actionFind, SIGNAL(triggered(bool)), this, SLOT(editorFindReplaceDialog()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(editorTabChanged(int)));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    connect(fr, SIGNAL(findRequest(QString, bool, bool, bool, bool)), this, SLOT(editorFindResponse(QString, bool, bool, bool, bool)));
    connect(fr, SIGNAL(replaceRequest(QString, QString, bool, bool, bool, bool, bool)), this, SLOT(editorReplaceResponse(QString,QString,bool, bool, bool, bool, bool)));

    /*
     * TODO: set up all action handlers
     */
}

void MainWindow::setIconStates(bool state)
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

void MainWindow::newFile()
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
    qsc->setFocus();
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
    setIconStates(true);
    D("New File");
}

void MainWindow::openFile()
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
            MainWindow::newFile();
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

void MainWindow::saveFile()
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

void MainWindow::saveFileAs()
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

void MainWindow::closeFile(const int& index)
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
                MainWindow::saveFile();
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

void MainWindow::closeFile()
{
    D("Close Current File");
    MainWindow::closeFile(ui->tabWidget->currentIndex());
}

void MainWindow::setupLexer(enum LexerType l)
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
        default: {
            break;
        }
    }
}

void MainWindow::editorFindReplaceDialog()
{
    fr->show();
    D("Find Dialog");
}

void MainWindow::editorFindResponse(QString string, bool re, bool cs, bool wo, bool wr)
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->findFirst(string, re, cs, wo, wr);
}

void MainWindow::editorReplaceResponse(QString from, QString to, bool re, bool cs, bool wo, bool wr, bool all)
{
    if (!all) {
        if (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->findFirst(from, re, cs, wo, wr))
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->replace(to);
    } else {
        while (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->findFirst(from, re, cs, wo, wr))
            ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->replace(to);
    }
}

void MainWindow::editorTabChanged(int index)
{
     D("Tab Changed to " + QString::number(index).toStdString());
}

void MainWindow::editorUpdate()
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

void MainWindow::editorModified(bool status)
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

void MainWindow::editorSelection()
{
    if (ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->selectedText().length() > 0) {
        D("Selected Text");
    } else {
        D("Deselected Text");
    }
}

void MainWindow::editorUndo()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->undo();
    D("Undo");
}

void MainWindow::editorRedo()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->redo();
    D("Redo");
}

void MainWindow::editorCut()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->cut();
    if (! ui->actionPaste->isEnabled()) {
        ui->actionPaste->setEnabled(true);
    }
    D("Cut");
}

void MainWindow::editorCopy()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->copy();
    if (! ui->actionPaste->isEnabled()) {
        ui->actionPaste->setEnabled(true);
    }
    D("Copy");
}

void MainWindow::editorPaste()
{
    ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor")->paste();
}

void MainWindow::toggleSymbols()
{
    if(ui->dockSymbols->isVisible() == true)
        ui->dockSymbols->close();
    else
        ui->dockSymbols->show();
}

void MainWindow::toggleCscope()
{
    if(ui->dockCscope->isVisible() == true)
        ui->dockCscope->close();
    else
        ui->dockCscope->show();
}

void MainWindow::toggleFiles()
{
    if(ui->dockFiles->isVisible() == true)
        ui->dockFiles->close();
    else
        ui->dockFiles->show();
}

void MainWindow::aboutDialog()
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

int MainWindow::getFirstTabIdFromName(QTabWidget *qtw, std::string name)
{
    for(int i = 0; i < qtw->count(); i++) {
        if(name == qtw->tabText(i).toStdString()) {
            return i;
        }
    }
    return -1;
}


MainWindow::~MainWindow()
{
    delete fr;
    delete ui;
}
