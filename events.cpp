/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file events.cpp
 */

#include <QMessageBox>
#include <QTabWidget>
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>

#include "ui_mainwindow.h"
#include <mainwindow.h>
#include <events.h>

#include <iostream>

/** @todo Move event handlers from mainwindow.cpp to here [DONE]
 *  @todo Also edit makefile to compile this source       [DONE]
 *  @todo Add Line Numbering
 *  @todo Add Custom highlighters
 *  @todo Add Multithreaded preprocessor for highlighter
 *  @todo Add Find&Replace
 *  @todo Add CScope wrapper
 *  @todo Refactor marked methods
 */

void MainWindow::newFile()
{
    /* TODO: Refactor this method */

    QTabWidget *qtw = new QTabWidget(this);
    QHBoxLayout *qhbl = new QHBoxLayout(qtw);
    QTextEdit *qte = new QTextEdit();
    highlighter = new Highlighter(qte->document());
    qte->setObjectName("editor"); //textview name
    qtw->setObjectName("tabs");
    qtw->setTabText(qtw->indexOf(qtw),"New File");
    qtw->setDocumentMode(true);
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    qhbl->addWidget(qte);
    qhbl->setMargin(9);
    ui->tabWidget->addTab(qtw, QString::fromStdString("New File"));
    ui->tabWidget->setCurrentWidget(qtw);
    setIconStates(true);
    statusBar()->showMessage("New File");
}

void MainWindow::openFile()
{
    /* TODO: Refactor this method */

    statusBar()->showMessage("Open File");
    QString fname = QFileDialog::getOpenFileName(this,
                                                 "Open File", "",
                                                 "All Files (*.*);;"
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
            QTextEdit *qte = ui->tabWidget->currentWidget()->findChild<QTextEdit *>("editor");
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            while (!stream.atEnd()) {
               QString line = stream.readLine();
               qte->append( line );
            }
        }
    }
}

void MainWindow::saveFile()
{
    /* TODO: Refactor this method */

    statusBar()->showMessage("Save File");
    QString fname = QFileDialog::getSaveFileName(this,
                                                    "Save File", "",
                                                    "All Files (*.*);;"
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
            QTextEdit *qte = ui->tabWidget->currentWidget()->findChild<QTextEdit *>("editor"); // !
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), finfo.fileName());
            stream << qte->toPlainText();
            f.close();
        }
    } else {
        statusBar()->showMessage("Save Canceled.");
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
