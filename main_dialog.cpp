#include "main_dialog.h"
#include "main_dialog.h"

Main_dialog::Main_dialog(bool& refNewGame, Game *g, QWidget *parent)
    : QMainWindow(parent)
    //, Game(g)
    , newGame(refNewGame)
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
    mNewGame = new QAction("&Nuova Partita", nullptr);
    mSave = new QAction("&Salva", nullptr);
    mEsci = new QAction("&Esci", nullptr);
    mFile->addAction(mNewGame);
    mFile->addSeparator();
    mFile->addAction(mSave);
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


    connect(mNewGame, SIGNAL(triggered(bool)), this, SLOT(newGameSlot()));
    //connect(mNewGame, SIGNAL(triggered(bool)), this, SLOT(saveGameSlot()));
    connect(mNewGame, SIGNAL(triggered(bool)), this, SLOT(close())); //TODO displayare una finestra e chiedere di salvare

    //connect(mSave, SIGNAL(triggered(bool)), this, SLOT(saveGameSlot())); //TODO same as above

    //connect(mEsci, SIGNAL(triggered(bool)), this, SLOT(saveGameSlot())); //TODO same as above

    connect(mEsci, SIGNAL(triggered(bool)), this, SLOT(close())); //TODO same as above

    connect(mShowInfo, SIGNAL(triggered(bool)), this, SLOT(showInf()));

    connect(mLegend, SIGNAL(triggered(bool)), this, SLOT(showLegend()));
}

void Main_dialog::newGameSlot()
{
    newGame = true;
}

void Main_dialog::showInf()
{
    QString str;
    str = QString("Applicazione creata da:\n\n %1\n %2\n %3").arg("Franchin Alessandro")
                                                             .arg("Pagotto Matteo")
                                                             .arg("Pagotto Manuel");

    QMessageBox::information(0, "Infomazioni", str);
}

void Main_dialog::showLegend()
{
    QString str;
    str = QString("%1\n%2\n%3").arg("P - Personaggio")
                               .arg("N - Nemico")
                               .arg("I - Oggetto");

    QMessageBox::information(0, "Legenda", str, "Capito");
}

