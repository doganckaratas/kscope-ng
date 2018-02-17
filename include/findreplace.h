#ifndef FINDREPLACE_H
#define FINDREPLACE_H

#include <QDialog>
#include <QString>

namespace Ui {
    class FindReplace;
}

class FindReplace : public QDialog
{
    Q_OBJECT

public:
    explicit FindReplace(QWidget *parent = 0);
    ~FindReplace();

private:
    Ui::FindReplace *ui;

private slots:
    void findClicked();
    void replaceClicked();
    void replaceAllClicked();


signals:
    void findRequest(QString string, bool re, bool cs, bool wo, bool wr);
    void replaceRequest(QString from, QString to, bool re, bool cs, bool wo, bool wr, bool all);
};

#endif // FINDREPLACE_H
