#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow_event_handler.h"
#include <iostream>
#include <QMessageBox>
#include <QTabWidget>
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle(QString::fromStdString("KScope-NG - ") +
                               QString::fromStdString(VERSION));
    /*
     *  remove above line from production release
     */
    tabIdx = 1;
    setupSignals();
    setIconStates(false);
}

void MainWindow::setupSignals()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutDialog()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
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
        ui->actionSave->setEnabled(true);
        ui->actionSave_All->setEnabled(true);
        ui->actionSave_As->setEnabled(true);
        ui->actionSelect_All->setEnabled(true);
        ui->actionCut->setEnabled(true);
        ui->actionCopy->setEnabled(true);
        ui->actionCopy_As_HTML->setEnabled(true);
        ui->actionPaste->setEnabled(true);
        ui->actionPrint->setEnabled(true);
        ui->actionUndo->setEnabled(true);
        ui->actionRedo->setEnabled(true);
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

int MainWindow::getFirstTabIdFromName(QTabWidget *qtw, std::string name)
{
    for(int i = 0; i < qtw->count(); i++) {
        if(name == qtw->tabText(i).toStdString()) {
            return i;
        }
    }
    return -1;
}

void MainWindow::newFile()
{
    QTabWidget *qtw = new QTabWidget(this);
    QHBoxLayout *qhbl = new QHBoxLayout(qtw);
    QTextEdit *qte = new QTextEdit();
    qte->setObjectName("editor"); //textview name
    qtw->setObjectName("tabs");
    qtw->setTabText(qtw->indexOf(qtw),"New File");
    qtw->setDocumentMode(true);
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    qhbl->addWidget(qte);
    qhbl->setMargin(9);
    ui->tabWidget->addTab(qtw, QString::fromStdString("New File"));
    setIconStates(true);
    statusBar()->showMessage("New File");
}

void MainWindow::openFile()
{
    statusBar()->showMessage("Open File");
}

void MainWindow::saveFile()
{
    statusBar()->showMessage("Save File");
    QFile f("/Users/dogan/Desktop/test.txt");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite)) {
        QTextStream stream(&f);
        QFileInfo finfo(f);
        QTextEdit *qte = ui->tabWidget->currentWidget()->findChild<QTextEdit *>("editor"); // !
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
        stream << qte->toPlainText();
        //change tab text
        f.close();
    }
}

void MainWindow::closeFile(const int& index)
{
    statusBar()->showMessage("Close File with idx");

    if (index == -1) {
        return;
    }
    ui->tabWidget->widget(index)->deleteLater();
    /*
     * MEMORY LEAK, delete tab content  & document too.
     */
    if (ui->tabWidget->count() <= 1) {
        setIconStates(false);
    }
}

void MainWindow::closeFile()
{
    statusBar()->showMessage("Close File single inst");
    int idx = ui->tabWidget->currentIndex();
    if (idx == -1) {
        return;
    }
    ui->tabWidget->widget(idx)->deleteLater();
    if (ui->tabWidget->count() <= 1) {
        setIconStates(false);
    }
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
    qm->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
