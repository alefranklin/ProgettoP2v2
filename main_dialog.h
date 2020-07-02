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
    Main_dialog(Game* g = nullptr, QWidget *parent = nullptr);

private:

    prova_main* mainWidget;
    QMenuBar* menubar;
    QMenu* mFile;
    QMenu* mHelp;
    QMenu* mInfo;
    QAction* mLogOut;
    QAction* mEsci;
    QAction* mLegend;
    QAction* mShowInfo;
    QAction* mShowRank;

    void setMenuBar();

public slots:

private slots:

};

#endif
