#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "findreplace2.h"

class View// : public QMainWindow
{
Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    ~View();
    void showFindReplace();

private:
    FindReplace2 *fr2;

signals:

public slots:

};

#endif // VIEW_H
