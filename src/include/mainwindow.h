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

#define RELEASE_DATE    "02/02/2018\n"
#define VERSION         "v0.6_PRE_RELEASE"
#define VER_STR         VERSION"\n"
#define D(arg)          statusBar()->showMessage("DEBUG: " + QString::fromStdString(arg),1000)

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
    int getFirstTabIdFromName(QTabWidget *qtw, std::string name);
    void setupSignals();
    void setIconStates(bool state);
    
private slots:
    void newFile();
    void openFile();
    void saveFile();
    void closeFile();
    void closeFile(const int& index);
    void editorSelection();
    void editorUpdate();
    void editorModified(bool status);
    void editorUndo();
    void editorRedo();
    void toggleSymbols();
    void toggleCscope();
    void toggleFiles();
    void aboutDialog();
};

#endif // MAINWINDOW_H
