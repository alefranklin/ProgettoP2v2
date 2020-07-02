#ifndef MAIN_DIALOG
#define MAIN_DIALOG

#include <QMainWindow>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QString>

#include <prova_main.h>

#include <string>

class Main_dialog : public QMainWindow {
    Q_OBJECT

public:
    Main_dialog(Game* g, QWidget *parent = nullptr);

private:

    prova_main* mainWidget;
    QMenuBar* menubar;
    QMenu* mbFile;
    QMenu* mbTools;
    QMenu* mbInfo;
    QAction* mbLogOut;
    QAction* mbEsci;
    QAction* mbTotalSize;
    QAction* mbInfoShow;

    void setMenuBar();

public slots:

private slots:

};

#endif
