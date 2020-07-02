#include "main_dialog.h"

Main_dialog::Main_dialog(Game *g, QWidget *parent)
    : QMainWindow(parent)
{

    setFixedSize(1024, 600);
    setMenuBar();

    mainWidget = new prova_main(g, parent);
    setCentralWidget(mainWidget);
}

void Main_dialog::setMenuBar()
{
    menubar = menuBar();
    //parent senza valore di default su alcune versioni di QT (ad esempio in laboratorio)
    mFile = new QMenu("&File", nullptr);
    mLogOut = new QAction("&Salva", nullptr);
    mEsci = new QAction("&Esci", nullptr);
    mFile->addAction(mLogOut);
    mFile->addSeparator();
    mFile->addAction(mEsci);
    menubar->addMenu(mFile);

    mInfo  = new QMenu("&Info", nullptr);
    mShowInfo = new QAction("I&nfo sviluppatori", nullptr);
    mShowRank = new QAction("&Rank", nullptr);
    mInfo->addAction(mShowInfo);
    menubar->addMenu(mInfo);

    mHelp = new QMenu("&Help", nullptr);
    mLegend = new QAction("&Legenda", nullptr);
    mHelp->addAction(mLegend);
    menubar->addMenu(mHelp);
}

