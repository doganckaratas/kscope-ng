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
#include "Qsci/qscilexer.h"
#include "Qsci/qscilexerpython.h"
#include "Qsci/qscilexercpp.h"
#include "Qsci/qscilexermakefile.h"

//#include "events.h"

#include <iostream>

/** === Roadmap ===
 *  @todo Implement Event.cpp, Action.cpp, View.cpp
 *  @todo Also edit makefile to compile this source       [DONE]
 *  @todo Add Line Numbering                              [DONE]
 *  @todo Add Custom highlighters                         [WIP*]
 *  @todo Add Multithreaded preprocessor for highlighter
 *  @todo Add Find&Replace
 *  @todo Add CScope wrapper
 *  @todo Refactor marked methods
 *  @todo Delete View XML and implement them with C++
 *  @todo Fix Windows release
 */


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(editorTabChanged(int)));
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
    qsc->setMarginType(0, QsciScintilla::NumberMargin);
    qsc->setMarginWidth(0, "0000");
    qsc->setMarginsForegroundColor(QColor("#ff888888"));
    qsc->setFocus();
    qtw->setTabText(qtw->indexOf(qtw), "New File");
    qtw->setDocumentMode(true);
    qtw->setObjectName("tab");
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    connect(qsc, SIGNAL(selectionChanged()), this, SLOT(editorSelection()));
    connect(qsc, SIGNAL(textChanged()), this, SLOT(editorUpdate()));
    connect(qsc, SIGNAL(modificationChanged(bool)), this, SLOT(editorModified(bool)));
    connect(qsc, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(qsc, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
    connect(ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(editorPaste()));
    qhbl->addWidget(qsc);
    qhbl->setMargin(0);
    qtw->setTabToolTip(qtw->currentIndex(),"New File");
    ui->tabWidget->addTab(qtw, QString::fromStdString("New File"));
    ui->tabWidget->setCurrentWidget(qtw);
    ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon(":/icons/icons/c_source.png"));
    ui->actionSave->setEnabled(false);
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
            QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
            //qsc->setLexer(new QsciLexerCPP(this));
            qsc->setFont(QFont("Ubuntu Mono", 12, QFont::Normal, false));
            qsc->setFocus();
            connect(qsc, SIGNAL(selectionChanged()), this, SLOT(editorSelection()));
            connect(qsc, SIGNAL(textChanged()), this, SLOT(editorUpdate()));
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            ui->tabWidget->setObjectName(fname);

            qsc->setText(stream.readAll());
            qsc->setModified(false);
            /* Newline should be selectable from users,
             * which should has three options
             * -> Unix (\n)
             * -> Windows (\r\n)
             * -> Classic MacOS (\r)
             */
        }
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(),fname);
    }

    D("Open File");
}

void MainWindow::saveFile()
{
    /* TODO: Merge with Save As */

    D("Save File");
    if (ui->tabWidget->tabToolTip(ui->tabWidget->currentIndex()) != "New File") {
        QFile f(currentFile);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite)) {
            QTextStream stream(&f);
            QFileInfo finfo(f);
            QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor"); // !
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            stream << qsc->text();
            f.close();
        }
    } else {
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
        if (f.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite)) {
            QTextStream stream(&f);
            QFileInfo finfo(f);
            QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor"); // !
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            stream << qsc->text();
            f.close();
            ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(),fname);
        }
    } else {
        D("Save Canceled.");
    }
}

void MainWindow::closeFile(const int& index)
{
    D("Close Tab File");

    if (index == -1) {
        return;
    }
    QsciScintilla *qsc = ui->tabWidget->widget(index)->findChild<QsciScintilla *>("editor");
    qsc->close();
    ui->tabWidget->widget(index)->deleteLater();
    qsc->deleteLater();
    /*
     * MEMORY LEAK, delete tab content  & document too. [DONE]
     */
    if (ui->tabWidget->count() <= 1) {
        setIconStates(false);
    }
}

void MainWindow::closeFile()
{
    D("Close Current File");
    int idx = ui->tabWidget->currentIndex();
    if (idx == -1) {
        return;
    }
    QsciScintilla *qsc = ui->tabWidget->widget(idx)->findChild<QsciScintilla *>("editor");
    qsc->close();
    qsc->deleteLater();
    ui->tabWidget->widget(idx)->deleteLater();
    if (ui->tabWidget->count() <= 1) {
        setIconStates(false);
    }
}

void MainWindow::editorTabChanged(int index)
{
     D("Tab Changed to " + index);
}

void MainWindow::editorUpdate()
{
    QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
    if (qsc->isUndoAvailable()) {
    // ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), "*" + ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
       /* TODO
        * Implement this correctly later
        */
        ui->actionUndo->setEnabled(true);
    } else {
        ui->actionUndo->setEnabled(false);
    }

    if (qsc->isRedoAvailable()) {
        ui->actionRedo->setEnabled(true);
    } else {
        ui->actionRedo->setEnabled(false);
    }
    D("Updated Text");
}

void MainWindow::editorModified(bool status)
{
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
    QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
    if (qsc->selectedText().length() > 0) {
        D("Selected Text");
    } else {
        D("Deselected Text");
    }
}

void MainWindow::editorUndo()
{
    QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
    qsc->undo();
    D("Undo");
}

void MainWindow::editorRedo()
{
    QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
    qsc->redo();
    D("Redo");
}

void MainWindow::editorCut()
{
    QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
    qsc->cut();
    if (! ui->actionPaste->isEnabled()) {
        ui->actionPaste->setEnabled(true);
    }
    D("Cut");
}

void MainWindow::editorCopy()
{
    QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
    qsc->copy();
    if (! ui->actionPaste->isEnabled()) {
        ui->actionPaste->setEnabled(true);
    }
    D("Copy");
}

void MainWindow::editorPaste()
{
    QsciScintilla *qsc = ui->tabWidget->currentWidget()->findChild<QsciScintilla *>("editor");
    qsc->paste();
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
    delete ui;
}
