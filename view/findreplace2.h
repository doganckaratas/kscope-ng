#ifndef FINDREPLACE2_H
#define FINDREPLACE2_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FindReplace2 : public QDialog
{
    Q_OBJECT
public:
    explicit FindReplace2(QWidget *parent = nullptr);
    ~FindReplace2();
    void show();

private:
    QDialog *fr_dialog;
    QTabWidget *fr_tabwidget;
    QWidget *fr_findtab;
    QWidget *fr_replacetab;
    QVBoxLayout *fr_tablayout;

signals:

public slots:
};

#endif // FINDREPLACE2_H
