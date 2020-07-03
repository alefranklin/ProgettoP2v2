#include "entergame.h"

#include <QDebug>

EnterGame::EnterGame(Player** pers,QWidget* parent): QDialog(parent), pg(pers)
{

    setWindowTitle("D&P2 - Seleziona Nome");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //setWindowIcon(QIcon(QPixmap(":/icona")));

    createLayoutEnterGame();
    QVBoxLayout* enterLayout = new QVBoxLayout;
    enterLayout->addLayout(layoutEnterGame);
    setLayout(enterLayout);
}

void EnterGame::cleanLabel()
{
   pg_name->clear();
   pg_name->setFocus();
}


void EnterGame::tryEnter()
{
    if(!pg_name->text().isEmpty() && pg_name->text() != " "){
        *pg = new Player(pg_name->text(), 20, 20); //TODO inizializzare con Game
        this->close();
    } else {
        QMessageBox msgError;
        msgError.setText("Errore: il nome non può essere vuoto");
        msgError.exec();
    }
}


void EnterGame::createLayoutEnterGame()
{
    layoutEnterGame = new QGridLayout();
    nameLabel = new QLabel();
    nameLabel->setText("Nome Personaggio:");

    pg_name = new QLineEdit();

    layoutEnterGame->addWidget(nameLabel, 1, 0);
    layoutEnterGame->addWidget(pg_name, 1, 1);


    bPlay = new QPushButton();
    bPlay->setText("Gioca");
    layoutEnterGame->addWidget(bPlay, 3, 0, 1, 2);
    connect(bPlay, SIGNAL(clicked()), this, SLOT(tryEnter()));

    setFixedSize(280,110);
}

