#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setupSignals();
}

void MainWindow::setupSignals()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::newFile()
{
    statusBar()->showMessage("NEW");
}

void MainWindow::openFile()
{
    statusBar()->showMessage("OPEN");
}

MainWindow::~MainWindow()
{
    delete ui;
}
