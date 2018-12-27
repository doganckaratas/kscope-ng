/**
 * @brief kscope-ng
 * A Qt based C/C++ IDE Project
 * @author Dogan C. Karatas
 * @date 2018
 * @file kscope.h
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "findreplace.h"
#include "cscope.h"

#define RELEASE_DATE    "28/02/2018\n"
#define VERSION         "v0.8_PRE_RELEASE"
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
    FindReplace *fr;
    CScope *cs;
    int getFirstTabIdFromName(QTabWidget *qtw, std::string name);
    void setupSignals();
    void setIconStates(bool state);
    QString cscope_bin = "cscope";
    enum LexerType{
        LEXER_DEFAULT = 0,
        LEXER_CPP,
        LEXER_PYTHON,
        LEXER_MAKEFILE,
        LEXER_JAVA
    };

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void closeFile(const int& index);

    void getFiles(QString files);


    void setupLexer(enum LexerType l);

    void editorTabChanged(int index);
    void editorSelection();
    void editorUpdate();
    void editorModified(bool status);
    void editorUndo();
    void editorRedo();

    void cscopeSetup(QString path);
    void cscopeQuery(int mode, QString keyword);
    void cscopeClear();
    void cscopeDestroy();
    void cscopeReferencesDialog();
    void cscopeDefinitionsDialog();
    void cscopeCalledFunctionsDialog();
    void cscopeCallingFunctionsDialog();
    void cscopeFindTextDialog();
    void cscopeFindEGrepDialog();
    void cscopeFindFileDialog();
    void cscopeIncludingFilesDialog();
    void cscopeResponse(int mode, QString keyword);

    void editorFindDialog();
    void editorReplaceDialog();
    void editorFindResponse(QString string, bool re, bool cs, bool wo, bool wr);
    void editorReplaceResponse(QString from, QString to, bool re, bool cs, bool wo, bool wr, bool all);

    void editorCut();
    void editorCopy();
    void editorPaste();
    void toggleSymbols();
    void toggleCscope();
    void toggleFiles();
    void aboutDialog();
};

#endif // MAINWINDOW_H
