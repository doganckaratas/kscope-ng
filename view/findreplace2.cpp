/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file findreplace.cpp
 */

#include <QWidget>
#include <QDialog>
#include <QTabWidget>
#include <iostream>
#include <QVBoxLayout>
#include "findreplace2.h"

FindReplace2::FindReplace2(QWidget *parent) : QDialog(parent)
{
    fr_dialog = new QDialog(parent);
    fr_tablayout = new QVBoxLayout();
    fr_tabwidget = new QTabWidget();
    fr_findtab = new QWidget();
    fr_replacetab = new QWidget();

    fr_tabwidget->addTab(fr_findtab, "Find");
    fr_tabwidget->addTab(fr_replacetab, "Replace");
    fr_tablayout->addWidget(fr_tabwidget);

    fr_dialog->setWindowModality(Qt::WindowModality::NonModal);
    fr_dialog->setWindowTitle("Find & Replace");
    fr_dialog->resize(415, 217);
    fr_dialog->setLayout(fr_tablayout);
}

void FindReplace2::show()
{

    fr_dialog->show();
}

FindReplace2::~FindReplace2()
{
    delete fr_dialog;
}

