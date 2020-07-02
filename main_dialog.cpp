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
    mbFile = new QMenu("File", nullptr);
    mbLogOut = new QAction("Cambia utente", nullptr);
    mbEsci = new QAction("Esci", nullptr);
    mbFile->addAction(mbLogOut);
    mbFile->addSeparator();
    mbFile->addAction(mbEsci);
    menubar->addMenu(mbFile);

    mbTools = new QMenu("Tools", nullptr);
    mbTotalSize = new QAction("Calcola dimensione totale", nullptr);
    mbTools->addAction(mbTotalSize);
    menubar->addMenu(mbTools);

    mbInfo  = new QMenu("Info", nullptr);
    mbInfoShow = new QAction("Info sullo sviluppatore", nullptr);
    mbInfo->addAction(mbInfoShow);
    menubar->addMenu(mbInfo);

}

