#include "game.h"

// per il random (provvisorio)
#include <QtGlobal>
#include <QTime>
#include <QFile>

const int Game::mapSize = 250;

const QString fileScore = "../Save.txt";


Game::Game(Character* player, QObject *parent) : QObject(parent)
  , miniMapSize(20) // 20 di degault
  , combat(nullptr)
  , pg(dynamic_cast<Player*>(player))
  , map(mapSize)
{
    //per il rand di test
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    //la grandezza della minimappa è settata quindi aggiorno la view
    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
}

Game::~Game(){}

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

void Game::saveScoreSlot(){
    QFile file(fileScore);

    qDebug() << "entro salva file";

    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        QTextStream outputStream(&file);

        outputStream << "Giocatore: " << pg->getName() << "\t Punteggio: " << score << "\n";

        file.close();
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



void Game::fight(Character *pg, QVector<Character *> enemies) {
}
