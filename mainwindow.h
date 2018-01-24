#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <highlighter.h>

#define RELEASE_DATE    "24/01/2018\n"
#define VERSION         "v0.3_PRE_RELEASE"
#define VER_STR         VERSION"\n"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int tabIdx;
    Highlighter *highlighter;
    int getFirstTabIdFromName(QTabWidget *qtw, std::string name);
    void setupSignals();
    void setIconStates(bool state);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void closeFile();
    void closeFile(const int& index);
    void aboutDialog();
};

#endif // MAINWINDOW_H
