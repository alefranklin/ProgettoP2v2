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
#include "game.h"

#include <string>

class Main_dialog : public QMainWindow {
    Q_OBJECT

public:
    explicit Main_dialog(bool& refNewGame, Game* g = nullptr, QWidget *parent = nullptr);
    ~Main_dialog(){}

private:

    prova_main* mainWidget;
    QMenuBar* menubar;
    QMenu* mFile;
    QMenu* mHelp;
    QMenu* mInfo;
    QAction* mNewGame;
    QAction* mSave;
    QAction* mEsci;
    QAction* mLegend;
    QAction* mShowInfo;
    QAction* mShowRank;

    bool& newGame;

    void setMenuBar();

public slots:
    void showLegend();
    void newGameSlot();

private slots:
    void showInf();

};

#endif
