#include "game.h"

// per il random (provvisorio)
#include <QtGlobal>
#include <QTime>

Game::Game(QObject *parent) : QObject(parent), combat(nullptr)
{

}

Game::~Game()
{
    //per il rand di test
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

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

int Game::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

void Game::move(char m) {
  switch (m) {
    case 'w': map.moveUP();     break;
    case 'a': map.moveLEFT();   break;
    case 's': map.moveDOWN();   break;
    case 'd': map.moveRIGHT();  break;
    default:  break;
  }
}

bool Game::isItem(const Entity *e) { return (dynamic_cast<const Item*>(e)) ? true : false; }
bool Game::isWeapon(const Entity *e) { return (dynamic_cast<const Weapon*>(e)) ? true : false; }
bool Game::isArmor(const Entity *e) { return (dynamic_cast<const Armor*>(e)) ? true : false; }
bool Game::isPotion(const Entity *e) { return (dynamic_cast<const Potion*>(e)) ? true : false; }
bool Game::isCharacter(const Entity *e) { return (dynamic_cast<const Character*>(e)) ? true : false; }
bool Game::isMob(const Entity *e) { return (dynamic_cast<const Mob*>(e)) ? true : false; }
bool Game::isPlayer(const Entity *e) { return (dynamic_cast<const Player*>(e)) ? true : false; }



void Game::fight(Character *pg, QVector<Character *> enemies) {
}
