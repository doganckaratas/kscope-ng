#include "findreplace.h"
#include "ui_findreplace.h"

FindReplace::FindReplace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindReplace)
{
    ui->setupUi(this);
}

FindReplace::~FindReplace()
{
    delete ui;
}
