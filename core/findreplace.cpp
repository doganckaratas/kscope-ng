#include "findreplace.h"
#include "ui_findreplace.h"

FindReplace::FindReplace(QWidget *parent) : QDialog(parent), ui(new Ui::FindReplace) {
    ui->setupUi(this);
    connect(ui->findButton, SIGNAL(clicked(bool)), this, SLOT(findClicked()));
    connect(ui->replaceButton, SIGNAL(clicked(bool)), this, SLOT(replaceClicked()));
    connect(ui->replaceAllButton, SIGNAL(clicked(bool)), this, SLOT(replaceAllClicked()));
    connect(ui->findCancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->replaceCancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void FindReplace::findClicked()
{
    emit findRequest(ui->findEditText->text(),
                     ui->findRegularExpressionCheckBox->isChecked(),
                     ui->findCaseSensitiveCheckBox->isChecked(),
                     ui->findExactWordCheckBox->isChecked(),
                     ui->findWrapSearchCheckBox->isChecked());
}

void FindReplace::replaceClicked()
{
    emit replaceRequest(ui->replaceFromEditText->text(),
                        ui->replaceToEditText->text(),
                        ui->replaceRegularExpressionCheckBox->isChecked(),
                        ui->replaceCaseSensitiveCheckBox->isChecked(),
                        ui->replaceExactWordCheckBox->isChecked(),
                        ui->replaceWrapSearchCheckBox->isChecked(),
                        false);
}

void FindReplace::replaceAllClicked()
{
    emit replaceRequest(ui->replaceFromEditText->text(),
                        ui->replaceToEditText->text(),
                        ui->replaceRegularExpressionCheckBox->isChecked(),
                        ui->replaceCaseSensitiveCheckBox->isChecked(),
                        ui->replaceExactWordCheckBox->isChecked(),
                        ui->replaceWrapSearchCheckBox->isChecked(),
                        true);
}

FindReplace::~FindReplace()
{
    delete ui;
}
