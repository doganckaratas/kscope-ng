#include "cscope.h"
#include "ui_cscope.h"

CScope::CScope(QWidget *parent) : QDialog(parent), ui(new Ui::CScope)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->executeButton, SIGNAL(clicked(bool)), this, SLOT(searchClicked()));
}

void CScope::showReferences()
{
    ui->typeComboBox->setCurrentIndex(0);
    this->show();
}

void CScope::showDefinitions()
{
    ui->typeComboBox->setCurrentIndex(1);
    this->show();
}

void CScope::showCalledFunctions()
{
    ui->typeComboBox->setCurrentIndex(2);
    this->show();
}

void CScope::showCallingFunctions()
{
    ui->typeComboBox->setCurrentIndex(3);
    this->show();
}

void CScope::showFindText()
{
    ui->typeComboBox->setCurrentIndex(4);
    this->show();
}

void CScope::showFindEGrep()
{
    ui->typeComboBox->setCurrentIndex(5);
    this->show();
}

void CScope::showFindFile()
{
    ui->typeComboBox->setCurrentIndex(7);
    this->show();
}

void CScope::showIncludingFiles()
{
    ui->typeComboBox->setCurrentIndex(8);
    this->show();
}


void CScope::searchClicked()
{
    emit cscopeRequest(ui->typeComboBox->currentIndex(), ui->symbolString->text());
}

CScope::~CScope()
{
    delete ui;
}
