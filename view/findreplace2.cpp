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
#include <QLabel>
#include <QPushButton>
#include "findreplace2.h"

FindReplace2::FindReplace2(QWidget *parent) : QDialog(parent)
{
    dialog = new QDialog(parent);
    tablayout = new QVBoxLayout();
    tabwidget = new QTabWidget();
    findtab = new QWidget();
    replacetab = new QWidget();

    findlayout = new QVBoxLayout();
    textboxctl_layout = new QHBoxLayout();
    comboctl1_layout = new QHBoxLayout();
    comboctl2_layout = new QHBoxLayout();
    buttonctl_layout = new QHBoxLayout();
    findspacer = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    findlabel = new QLabel();
    findtext = new QLineEdit();
    regexcheck = new QCheckBox();
    casecheck = new QCheckBox();
    exactcheck = new QCheckBox();
    wrapcheck = new QCheckBox();
    findbutton = new QPushButton();
    cancelbutton = new QPushButton();

    replacelayout = new QVBoxLayout();
}

void FindReplace2::setupFindView()
{
    tabwidget->addTab(findtab, "Find");

    findlabel->setText("Find: ");
    textboxctl_layout->addWidget(findlabel);
    textboxctl_layout->addWidget(findtext);
    findlayout->addLayout(textboxctl_layout);

    findlayout->addItem(findspacer);

    regexcheck->setText("Regular Expression");
    casecheck->setText("Case Sensitive");
    comboctl1_layout->addWidget(regexcheck);
    comboctl1_layout->addWidget(casecheck);
    findlayout->addLayout(comboctl1_layout);

    exactcheck->setText("Exact Word Match");
    wrapcheck->setText("Word Wrap");
    comboctl2_layout->addWidget(exactcheck);
    comboctl2_layout->addWidget(wrapcheck);
    findlayout->addLayout(comboctl2_layout);

    findbutton->setText("Find");
    cancelbutton->setText("Cancel");
    buttonctl_layout->addWidget(findbutton);
    buttonctl_layout->addWidget(cancelbutton);
    findlayout->addLayout(buttonctl_layout);

    findtab->setLayout(findlayout);
}

void FindReplace2::setupReplaceView()
{
    tabwidget->addTab(replacetab, "Replace");
    tablayout->addWidget(tabwidget);
}

void FindReplace2::setupView()
{
    setupFindView();
    setupReplaceView();
    dialog->setWindowModality(Qt::WindowModality::NonModal);
    dialog->setWindowTitle("Find & Replace");
    dialog->resize(415, 217);
    dialog->setLayout(tablayout);
}

void FindReplace2::show()
{
    setupView();
    dialog->show();
}

FindReplace2::~FindReplace2()
{
    delete dialog;
}

