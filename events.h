#ifndef MAINWINDOW_EVENT_HANDLER
#define MAINWINDOW_EVENT_HANDLER

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Events
{

public:

private:

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void closeFile();
    void closeFile(const int& index);
    void aboutDialog();
};

#endif // MAINWINDOW_EVENT_HANDLER

