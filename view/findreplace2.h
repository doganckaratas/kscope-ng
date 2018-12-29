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
    QWidget *replacetab;
    QVBoxLayout *findlayout;
    QVBoxLayout *replacelayout;
    QHBoxLayout *findtextboxctl1_layout;
    QHBoxLayout *findtextboxctl2_layout;
    QHBoxLayout *replacetextboxctl_layout;
    QHBoxLayout *findcomboctl1_layout;
    QHBoxLayout *findcomboctl2_layout;
    QHBoxLayout *replacecomboctl1_layout;
    QHBoxLayout *replacecomboctl2_layout;
    QHBoxLayout *findbuttonctl_layout;
    QHBoxLayout *replacebuttonctl_layout;
    QSpacerItem *findspacer;
    QSpacerItem *replacespacer;
    QLabel *findlabel1;
    QLabel *findlabel2;
    QLabel *replacelabel;
    QLineEdit *findtext1;
    QLineEdit *findtext2;
    QLineEdit *replacetext;
    QCheckBox *findregexcheck;
    QCheckBox *findcasecheck;
    QCheckBox *findexactcheck;
    QCheckBox *findwrapcheck;
    QCheckBox *replaceregexcheck;
    QCheckBox *replacecasecheck;
    QCheckBox *replaceexactcheck;
    QCheckBox *replacewrapcheck;
    QPushButton *findbutton;
    QPushButton *replacebutton;
    QPushButton *replaceallbutton;
    QPushButton *findcancelbutton;
    QPushButton *replacecancelbutton;

    void initializeComponents();
    void setupInterface();
    void setupFindInterface();
    void setupReplaceInterface();

signals:

public slots:
};

#endif // FINDREPLACE2_H
