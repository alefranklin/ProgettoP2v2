#include "game.h"

// per il random (provvisorio)
#include <QtGlobal>
#include <QTime>
#include <QFile>

const int Game::mapSize = 250;

const QString Game::fileScore = "../Save.txt";


Game::Game(Player* player, QObject *parent) : QObject(parent)
  , miniMapSize(20) // 20 di degault
  , combat(nullptr)
  , pg(player)
  , map(mapSize)
{
    //per il rand di test
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    //la grandezza della minimappa è settata quindi aggiorno la view
    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
}

Game::~Game()
{
    qDebug() << "Distruttore game";
    if(pg) {
        delete pg;
        qDebug() << "Elimino pg";
    }

}

void Game::dialog(QString s)
{
    emit dialogOut(s);
    emit choiceOut(Choice::escape());

}

void Game::choiceDone(Choice c)
{
    emit dialogOut("scelta fatta:"+c.getLabel());
    emit dialogOut("adesso devo gestire le varie funzioni delle scelte");


    switch(c) {
    // scappa
    case 0:
        scappa();
        break;
    default:
        break;
    }

}

void Game::usePotionMana() { emit dialogOut("sto usando la pozione del mana"); }

void Game::usePotionHealth() { emit dialogOut("sto usando la pozione della vita"); }

void Game::startCombat(Tile &t) {
    combat = new CombatState(t.e, nullptr);
    emit dialogOut("sei entrato nel pieno del combattimento");
    emit dialogOut("il tuo nemico ti sferra un fendente micidiale");
    // usare combat per tenere traccia dello stato del sistema
    combat->numero_turno++;
    combat->turno_player = true;
    emit dialogOut("cosa vuoi fare?");
    emit choiceOut(Choice::attack());
    //ememies.arma.use(player)
}

void Game::attacca() {
    emit dialogOut("usi la tua arma pazzesca per sfonnare il nemico");
}

void Game::endCombat() {
    delete combat;
    combat = nullptr;
}

int Game::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

void Game::move(char m) {
    switch (m) {
    case 'W': map.moveUP();     break;
    case 'A': map.moveLEFT();   break;
    case 'S': map.moveDOWN();   break;
    case 'D': map.moveRIGHT();  break;
    default:  break;
  }

  emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
}

void Game::onSetMiniMapSize(int s) {
    if(s > 0 && s <= map.getMapDimension() && s != miniMapSize) miniMapSize = s;
    else miniMapSize = mapSize;

    //la grandezza è cambiata quindi aggiorno la mappa
    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
}

void Game::saveScoreSlot(){
    QFile file(fileScore);

    qDebug() << "entro salva file";

    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        QTextStream outputStream(&file);

        outputStream << "Giocatore: " << pg->getName() << "\t Punteggio: " << score << "\n";

        file.close();
    }

}

void Game::savePlayerSlot()
{
    QString filePlayer = QFileDialog::getSaveFileName(Q_NULLPTR, "Save Player", "../", "File Player(*.fpg)");

    if(filePlayer.isEmpty()) return;
    else {
        QFile file(filePlayer);

        if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, "Unable to open file", file.errorString());
            return;
        }

        QJsonObject json; //= QJsonObject::fromVariantMap(v_map);

        json["nome"] = pg->getName();
        json["vita"] = pg->getVita();
        json["mana"] = pg->getMana();

        QJsonDocument d_json;
        d_json.setObject(json);

        file.write(d_json.toJson());

        file.close();
    }
}

void Game::loadPlayerSlot(bool)
{
    QString filePlayer = QFileDialog::getOpenFileName(Q_NULLPTR
                                                      , "Carica file Personaggio"
                                                      , "../"
                                                      , "File Player(*.fpg);;All files(*)");

    if(filePlayer.isEmpty()) return;
    else {
        QFile f(filePlayer);

        if(!f.open(QIODevice::ReadOnly)){
            QMessageBox::warning(Q_NULLPTR, "Impossibile aprire il file", f.errorString());
            return;
        }
        QString on_json = f.readAll();

        QJsonDocument d_json = QJsonDocument::fromJson(on_json.toUtf8());
        QJsonObject json = d_json.object();


        qDebug() << json["nome"].toString();


        pg = new Player(json["nome"].toString(), json["vita"].toInt(), json["mana"].toInt());
    }

}

void Game::scappa() {
    emit dialogOut("sto provando a scappare");
    // con una certa probabilita scappa
    if(randInt(0,1)) {
        moveBack();
        emit dialogOut("sono scappato");
    }
    else {
        emit dialogOut("non sei riuscito a scappare!");
        //startCombat();
    }
}



bool Game::isItem(const Entity *e) { return (dynamic_cast<const Item*>(e)) ? true : false; }
bool Game::isWeapon(const Entity *e) { return (dynamic_cast<const Weapon*>(e)) ? true : false; }
bool Game::isArmor(const Entity *e) { return (dynamic_cast<const Armor*>(e)) ? true : false; }
bool Game::isPotion(const Entity *e) { return (dynamic_cast<const Potion*>(e)) ? true : false; }
bool Game::isCharacter(const Entity *e) { return (dynamic_cast<const Character*>(e)) ? true : false; }
bool Game::isMob(const Entity *e) { return (dynamic_cast<const Mob*>(e)) ? true : false; }
bool Game::isPlayer(const Entity *e) { return (dynamic_cast<const Player*>(e)) ? true : false; }
bool Game::isSword(const Entity *e) { return (dynamic_cast<const Sword*>(e)) ? true : false;}
bool Game::isBow(const Entity *e) { return (dynamic_cast<const Bow*>(e)) ? true : false;}
bool Game::isMagicWeapon(const Entity *e) { return (dynamic_cast<const MagicWeapon*>(e)) ? true : false;}

Character *Game::getPlayer()
{
    return pg;
}
