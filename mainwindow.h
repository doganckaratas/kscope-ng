/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file mainwindow.h
 */

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
};

#endif // MAINWINDOW_H
