#include "findreplace.h"
#include "ui_findreplace.h"

FindReplace::FindReplace(QWidget *parent) : QDialog(parent), ui(new Ui::FindReplace) {
    ui->setupUi(this);
    connect(ui->findButton, SIGNAL(clicked(bool)), this, SLOT(findFirstClicked()));
}

void FindReplace::findFirstClicked()
{
    emit findFirstRequest(ui->findEditText->text(),
                     ui->findRegularExpressionCheckBox->isChecked(),
                     ui->findCaseSensitiveCheckBox->isChecked(),
                     ui->findExactWordCheckBox->isChecked(),
                     ui->findWrapSearchCheckBox->isChecked());
}

FindReplace::~FindReplace()
{
    delete ui;
}
