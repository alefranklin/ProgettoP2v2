#include "entergame.h"

#include "player.h"
#include "item.h"
#include "weapon.h"
#include "sword.h"
#include "bow.h"
#include "magicweapon.h"
#include "potion.h"
#include "armor.h"

#include <QFileDialog>
#include <QJsonArray>
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
    connect(bLoadPlayer, &QPushButton::clicked, this, &EnterGame::loadPlayerSlot);

    connect(bLoadPlayer, SIGNAL(clicked()), this, SLOT(tryEnter()));

    setFixedSize(280,110);
}

void EnterGame::loadPlayerSlot()
{
    QString filePlayer = QFileDialog::getOpenFileName(Q_NULLPTR
                                                      , "Carica file Personaggio"
                                                      , "../"
                                                      , "File Player(*.json)");


//    if(filePlayer.isEmpty()) return;
//    else {
//        QFile f(filePlayer);

//        if(!f.open(QIODevice::ReadOnly)){
//            QMessageBox::warning(Q_NULLPTR, "Impossibile aprire il file", f.errorString());
//            //emit warningFile(f.errorString());
//            return;
//        }
//        QString on_json = f.readAll();

//        QJsonParseError jsonError;

//        QJsonDocument d_json = QJsonDocument::fromJson(on_json.toUtf8(), &jsonError);

//        if(!jsonError.error){

//            QJsonObject json = d_json.object();

//            Player* pg = new Player(json["nome"].toString().toStdString(), json["vita"].toInt(), json["mana"].toInt());
//            *gioco = new Game(pg);
//        } else {
//            QMessageBox::warning(0,"ERROR", jsonError.errorString());
//        }
//    }

    if(filePlayer.isEmpty()) return;
    else {
        QFile file(filePlayer);

        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::warning(Q_NULLPTR, "Impossibile aprire il file", file.errorString());
            return;
        }

        QByteArray jsonData = file.readAll();

        file.close();

        QJsonDocument document = QJsonDocument::fromJson(jsonData);

        QJsonObject pg = document.object().value("Caratteristiche").toObject();//.toArray();
        QJsonObject arma = document.object().value("Arma").toObject();
        QJsonObject armatura = document.object().value("Armatura").toObject();
        QJsonArray inventario = document.object().value("Inventario").toArray();


        //bool corrotto = false;

//        vector<item*> itemsToLoad;
//        vector<item*> buildToLoad;
       if(!pg.isEmpty() && !arma.isEmpty() && !armatura.isEmpty()) {
            Player* p = new Player(pg["Nome"].toString().toStdString(), pg["Vita"].toString().toInt(), pg["Mana"].toString().toInt());
            p->setVitaMax(pg["vitaMax"].toString().toInt());
            p->setManaMax(pg["manaMax"].toString().toInt());

            Item *n = Game::JsonToItem(arma);
            Item *old;
            if(n) {
                Item *old = p->setWeapon(n);
                delete old;
            }
            n = Game::JsonToItem(armatura);
            if(n) {
                old = p->setArmor(n);
                delete old;
            }

           foreach (const QJsonValue &value, inventario) {
                QJsonObject obj = value.toObject();
                Item *i = Game::JsonToItem(obj);
                if(i) p->inventoryAdd(i);
            }


            //p->setWeapon()
            *gioco = new Game(p);
       }
    }
}


