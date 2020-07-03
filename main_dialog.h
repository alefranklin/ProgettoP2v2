#ifndef MAIN_DIALOG
#define MAIN_DIALOG

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

#include "prova_main.h"
#include "game.h"

#include <string>

class Main_dialog : public QMainWindow {
    Q_OBJECT

public:
    explicit Main_dialog(bool& refNewGame, Game* g, QWidget *parent = nullptr);
    ~Main_dialog(){}

private:


    Game* game;

    prova_main* mainWidget;
    QMenuBar* menubar;
    QMenu* mFile;
    QMenu* mHelp;
    QMenu* mInfo;
    QAction* mNewGame;
    QAction* mSavePlayer;
    QAction* mSave;
    QAction* mEsci;
    QAction* mLegend;
    QAction* mShowInfo;
    QAction* mShowRank;

    bool& newGame;

    void setMenuBar();

signals:
    void saveScoreSignal();

public slots:
    void showLegend();
    void newGameSlot();

private slots:
    void showInf();
    void confirmSave();

};

#endif
