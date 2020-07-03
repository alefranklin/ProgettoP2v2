#include "entergame.h"

#include <QDebug>

EnterGame::EnterGame(Game** g, QWidget* parent): QDialog(parent), gioco(g)
{

    setWindowTitle("D&P2 - Seleziona Nome");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

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
    if((!pg_name->text().isEmpty() && pg_name->text() != " ") || (*gioco)->getPlayer()){
        if(!(*gioco)->getPlayer()){
            //evito memory leak
            delete *gioco;
            Player* pg = new Player(pg_name->text(), 20, 20);
            *gioco = new Game(pg);
        }

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
    nameLabel = new QLabel("Nome Personaggio:");

    pg_name = new QLineEdit();

    layoutEnterGame->addWidget(nameLabel, 1, 0);
    layoutEnterGame->addWidget(pg_name, 1, 1);


    bPlay = new QPushButton("Gioca");
    layoutEnterGame->addWidget(bPlay, 3, 0, 1, 2);
    connect(bPlay, SIGNAL(clicked()), this, SLOT(tryEnter()));

    bLoadPlayer = new QPushButton("Carica Personaggio");
    layoutEnterGame->addWidget(bLoadPlayer, 4, 0);
    connect(bLoadPlayer, &QPushButton::clicked, *gioco, &Game::loadPlayerSlot);
    //connect(bPlay, SIGNAL(clicked()), this, SLOT(tryEnter()));

    //if((*gioco)->getPlayer()) nameLabel->setText((*gioco)->getPlayer()->getName());

    setFixedSize(280,110);
}

