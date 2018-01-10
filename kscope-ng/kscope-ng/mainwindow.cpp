#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
