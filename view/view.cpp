/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file view.cpp
 */


/* kscope.cpp ile degistirilecek */

#include "view.h"
#include <QMainWindow>
#include <QApplication>

View::View(QWidget *parent)// : QMainWindow(parent)
{
    fr2 = new FindReplace2();
}

void View::showFindReplace()
{
    fr2->show();
}

View::~View()
{
    delete fr2;
}
