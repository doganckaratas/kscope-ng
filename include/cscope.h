#ifndef CSCOPE_H
#define CSCOPE_H

#include <QDialog>
#include <QString>

namespace Ui {
    class CScope;
}

class CScope : public QDialog
{
    Q_OBJECT

public:
    explicit CScope(QWidget *parent = 0);
    void showReferences();
    void showDefinitions();
    void showCalledFunctions();
    void showCallingFunctions();
    void showFindText();
    void showFindEGrep();
    void showFindFile();
    void showIncludingFiles();
    ~CScope();

private:
    Ui::CScope *ui;

private slots:
    void searchClicked();

signals:
    void cscopeRequest(int mode, QString keyword);
};

#endif // CSCOPE_H
