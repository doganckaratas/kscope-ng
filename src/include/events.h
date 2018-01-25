/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file events.h
 */

#ifndef MAINWINDOW_EVENT_HANDLER
#define MAINWINDOW_EVENT_HANDLER

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Events
{

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void closeFile();
    void closeFile(const int& index);
    void aboutDialog();
};

#endif // MAINWINDOW_EVENT_HANDLER

