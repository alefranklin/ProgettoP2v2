#include "entergame.h"

#include "player.h"

#include <QDebug>

EnterGame::EnterGame(Game** g, QWidget* parent): QDialog(parent), gioco(g)
{

    setWindowTitle("D&P2 - Seleziona Nome");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //*gioco = new Game(nullptr);

    createLayoutEnterGame();
    QVBoxLayout* enterLayout = new QVBoxLayout;
    enterLayout->addLayout(layoutEnterGame);
    setLayout(enterLayout);
}

void EnterGame::cleanEnter()
{
   pg_name->clear();
   pg_name->setFocus();
}


void EnterGame::tryEnter()
{
    //regex str ("([a-z][A-Z])(.+)");
    if((!pg_name->text().isEmpty() /*&& regex_match(pg_name->text(), str)*/ ) || (*gioco)->getPlayer()){
        if(!(*gioco)->getPlayer()){
            //evito memory leak
            //qDebug() << "cancello gioco";
            //delete *gioco;
            //se faccio delete su gioco non posso più caricare il personaggio
            Player* pg = new Player(pg_name->text().toStdString(), 20, 20);
            *gioco = new Game(pg);
        }
        //qDebug() << "enter game _ gioco : " << &(*gioco);
        this->close();

    } else {
        QMessageBox msgError;
        msgError.setText("Errore durante la creazione del personaggio.");
        msgError.exec();
    }
}


void EnterGame::createLayoutEnterGame()
{
    layoutEnterGame = new QGridLayout();


    pg_name = new QLineEdit();
    pg_name->setPlaceholderText("Nome personaggio");

    layoutEnterGame->addWidget(pg_name, 1, 0, 1, 2);


    bPlay = new QPushButton("Gioca");
    layoutEnterGame->addWidget(bPlay, 3, 0, 1, 2);
    connect(bPlay, SIGNAL(clicked()), this, SLOT(tryEnter()));

    bLoadPlayer = new QPushButton("Carica Personaggio");
    layoutEnterGame->addWidget(bLoadPlayer, 4, 0);
    connect(bLoadPlayer, &QPushButton::clicked, *gioco, &Game::loadPlayerSlot);

    //errore load personaggio da file
    connect(*gioco, &Game::loadPlayerFromFile, this, &EnterGame::errorLoadPlayer);

    connect(bLoadPlayer, SIGNAL(clicked()), this, SLOT(tryEnter()));


    //connect(bPlay, SIGNAL(clicked()), this, SLOT(tryEnter()));

    //if((*gioco)->getPlayer()) nameLabel->setText((*gioco)->getPlayer()->getName());

    setFixedSize(280,110);
}

void EnterGame::errorLoadPlayer(QJsonParseError jsonError)
{
    QMessageBox::warning(0,"ERROR", jsonError.errorString());
}

