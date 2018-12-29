#ifndef FINDREPLACE2_H
#define FINDREPLACE2_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

class FindReplace2 : public QDialog
{
    Q_OBJECT
public:
    explicit FindReplace2(QWidget *parent = nullptr);
    ~FindReplace2();
    void show();

private:
    QDialog *dialog;
    QTabWidget *tabwidget;
    QVBoxLayout *tablayout;

    QWidget *findtab;
    QVBoxLayout *findlayout;
    QHBoxLayout *textboxctl_layout;
    QHBoxLayout *comboctl1_layout;
    QHBoxLayout *comboctl2_layout;
    QHBoxLayout *buttonctl_layout;
    QSpacerItem *findspacer;
    QLabel *findlabel;
    QLineEdit *findtext;
    QCheckBox *regexcheck;
    QCheckBox *casecheck;
    QCheckBox *exactcheck;
    QCheckBox *wrapcheck;
    QPushButton *findbutton;
    QPushButton *cancelbutton;

    QWidget *replacetab;
    QVBoxLayout *replacelayout;

    void setupFindView();
    void setupReplaceView();
    void setupView();

signals:

public slots:
};

#endif // FINDREPLACE2_H
