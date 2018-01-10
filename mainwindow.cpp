#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setupSignals()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
}

void MainWindow::newFile()
{
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

MainWindow::~MainWindow()
{
    delete ui;
}
