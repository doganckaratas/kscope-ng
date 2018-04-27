#ifndef FINDREPLACE_H
#define FINDREPLACE_H

#include <QDialog>

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
signals:

public slots:
};

#endif // FINDREPLACE_H
