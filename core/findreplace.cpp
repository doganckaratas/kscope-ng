/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file findreplace.cpp
 */

#include "findreplace.h"
#include "ui_findreplace.h"

/** === Roadmap ===
 *  @todo add cursor position to replace all, and cycle once
 *  @todo
 */


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

void FindReplace::showFind()
{
    ui->findReplaceTabWidget->setCurrentIndex(0);
    this->show();
}

void FindReplace::showReplace()
{
    ui->findReplaceTabWidget->setCurrentIndex(1);
    this->show();
}

FindReplace::~FindReplace()
{
    delete ui;
}
