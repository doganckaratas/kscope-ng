#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTabWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSignals();
}

void MainWindow::setupSignals()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutDialog()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::newFile()
{
    QTabWidget *qtw = new QTabWidget(this);
    QHBoxLayout *qhbl = new QHBoxLayout(qtw);
    QTextEdit *qte = new QTextEdit();
    qtw->setTabText(qtw->indexOf(qtw),"New File");
    qtw->setDocumentMode(true);
    qhbl->addWidget(qte);
    qhbl->setMargin(9);
    ui->tabWidget->addTab(qtw, QString::fromStdString("New File"));
    statusBar()->showMessage("New File");
}

void MainWindow::openFile()
{
    statusBar()->showMessage("Open File");
}

void MainWindow::saveFile()
{
    statusBar()->showMessage("Save File");
}

void MainWindow::aboutDialog()
{
    QMessageBox *qm = new QMessageBox(this);
    qm->setMinimumHeight(60);
    qm->setWindowTitle("About");
    qm->setText("Hello, this is About Box,\n"
                "Fill here with license, author, version, etc.\n"
                "~~~~~~~~~~~~~~~~~~~~~~~~\n");
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
