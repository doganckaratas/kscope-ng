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
};

#endif // FINDREPLACE_H
