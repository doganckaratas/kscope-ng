#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void closeFile();
    void closeFile(const int& index);
    void aboutDialog();
};

#endif // MAINWINDOW_H
