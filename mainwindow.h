#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define RELEASE_DATE    "12/01/2018\n"
#define VERSION         "v0.2_PRE_RELEASE"
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
