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
    void findFirstClicked();

signals:
    void findFirstRequest(QString string, bool re, bool cs, bool wo, bool wr);
};

#endif // FINDREPLACE_H
