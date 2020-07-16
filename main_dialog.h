#ifndef MAIN_DIALOG
#define MAIN_DIALOG

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

#include "main_view.h"
#include "game.h"

#include <string>

class main_dialog : public QMainWindow {
    Q_OBJECT

public:
    explicit main_dialog(bool& refNewGame, Game* g, QWidget *parent = nullptr);
    ~main_dialog(){}

private:
    Game* game;

    main_view* mainWidget;
    QMenuBar* menubar;
    QMenu* mFile;
    QMenu* mHelp;
    QMenu* mInfo;
    QAction* mNewGame;
    QAction* mSavePlayer;

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
    void onDie();

private slots:
    void showInf();
    void confirmSavePunt();
    void confirmSavePg();

    void savePlayerToJson();
};

#endif
