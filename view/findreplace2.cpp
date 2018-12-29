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
    initializeComponents();
    setupInterface();
}

void FindReplace2::initializeComponents()
{
    tablayout = new QVBoxLayout();
    tabwidget = new QTabWidget();

    findtab = new QWidget();
    findlayout = new QVBoxLayout();
    findtextboxctl1_layout = new QHBoxLayout();
    findcomboctl1_layout = new QHBoxLayout();
    findcomboctl2_layout = new QHBoxLayout();
    findbuttonctl_layout = new QHBoxLayout();
    findspacer = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    findlabel1 = new QLabel();
    findtext1 = new QLineEdit();
    findregexcheck = new QCheckBox();
    findcasecheck = new QCheckBox();
    findexactcheck = new QCheckBox();
    findwrapcheck = new QCheckBox();
    findbutton = new QPushButton();
    findcancelbutton = new QPushButton();

    replacetab = new QWidget();
    replacelayout = new QVBoxLayout();
    findtextboxctl2_layout = new QHBoxLayout();
    replacetextboxctl_layout = new QHBoxLayout();
    replacecomboctl1_layout = new QHBoxLayout();
    replacecomboctl2_layout = new QHBoxLayout();
    replacebuttonctl_layout = new QHBoxLayout();
    replacespacer = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);
    findlabel2 = new QLabel();
    findtext2 = new QLineEdit();
    replaceregexcheck = new QCheckBox();
    replacecasecheck = new QCheckBox();
    replaceexactcheck = new QCheckBox();
    replacewrapcheck = new QCheckBox();
    replacelabel = new QLabel();
    replacetext = new QLineEdit();
    replacebutton = new QPushButton();
    replaceallbutton = new QPushButton();
    replacecancelbutton = new QPushButton();
}

void FindReplace2::setupInterface()
{
    setupFindInterface();
    setupReplaceInterface();
    dialog->setWindowModality(Qt::WindowModality::NonModal);
    dialog->setWindowTitle("Find & Replace");
    dialog->resize(415, 257);
    tablayout->addWidget(tabwidget);
    dialog->setLayout(tablayout);
}

void FindReplace2::setupFindInterface()
{
    tabwidget->addTab(findtab, "Find");
    tabwidget->addTab(replacetab, "Replace");
    findlabel1->setText("Find: ");
    findlabel1->setMinimumSize(100, 0);
    findregexcheck->setText("Regular Expression");
    findcasecheck->setText("Case Sensitive");
    findexactcheck->setText("Exact Word Match");
    findwrapcheck->setText("Word Wrap");
    findbutton->setText("Find");
    findcancelbutton->setText("Cancel");

    findtextboxctl1_layout->addWidget(findlabel1);
    findtextboxctl1_layout->addWidget(findtext1);
    findcomboctl1_layout->addWidget(findregexcheck);
    findcomboctl1_layout->addWidget(findcasecheck);
    findcomboctl2_layout->addWidget(findexactcheck);
    findcomboctl2_layout->addWidget(findwrapcheck);
    findbuttonctl_layout->addWidget(findbutton);
    findbuttonctl_layout->addWidget(findcancelbutton);

    findlayout->addLayout(findtextboxctl1_layout);
    findlayout->addItem(findspacer);
    findlayout->addLayout(findcomboctl1_layout);
    findlayout->addLayout(findcomboctl2_layout);
    findlayout->addLayout(findbuttonctl_layout);
    findtab->setLayout(findlayout);
}

void FindReplace2::setupReplaceInterface()
{
    findlabel2->setText("Find: ");
    findlabel2->setMinimumSize(100, 0);
    replacelabel->setText("Replace: ");
    replacelabel->setMinimumSize(100, 0);
    replaceregexcheck->setText("Regular Expression");
    replacecasecheck->setText("Case Sensitive");
    replaceexactcheck->setText("Exact Word Match");
    replacewrapcheck->setText("Word Wrap");
    replacebutton->setText("Replace");
    replaceallbutton->setText("Replace All");
    replacecancelbutton->setText("Cancel");

    findtextboxctl2_layout->addWidget(findlabel2);
    findtextboxctl2_layout->addWidget(findtext2);
    replacetextboxctl_layout->addWidget(replacelabel);
    replacetextboxctl_layout->addWidget(replacetext);
    replacecomboctl1_layout->addWidget(replaceregexcheck);
    replacecomboctl1_layout->addWidget(replacecasecheck);
    replacecomboctl2_layout->addWidget(replaceexactcheck);
    replacecomboctl2_layout->addWidget(replacewrapcheck);
    replacebuttonctl_layout->addWidget(replacebutton);
    replacebuttonctl_layout->addWidget(replaceallbutton);
    replacebuttonctl_layout->addWidget(replacecancelbutton);

    replacelayout->addLayout(findtextboxctl2_layout);
    replacelayout->addLayout(replacetextboxctl_layout);
    replacelayout->addItem(replacespacer);
    replacelayout->addLayout(replacecomboctl1_layout);
    replacelayout->addLayout(replacecomboctl2_layout);
    replacelayout->addLayout(replacebuttonctl_layout);
    replacetab->setLayout(replacelayout);
}

void FindReplace2::show()
{
    dialog->show();
}

FindReplace2::~FindReplace2()
{
    delete dialog;
}

