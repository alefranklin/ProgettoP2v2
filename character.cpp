#include "character.h"
#include "entity.h"
#include <QVector>

#include <QDebug>


using namespace std;

  //CLASSE CHARACTER
  Character::Character(QString n, int v, int m): name(n), vita(v), mana(m), Entity() { qDebug() << "istanzio Character: " << endl; }
  QString Character::getName() { return name; }
  int Character::getVita() { return vita; }
  int Character::getMana() { return mana; }
  void Character::setDamage(int d) { vita = (vita-d >= 0) ? vita-d : 0; isAlive();}
  int Character::attacca(QVector<Character*> target) { return arma->use(this, target);}

  //CLASSE PLAYER
  Player::Player(QString n, int v, int m): Character(n, v, m) {}
  void Player::info() { qDebug() << "sono Player " << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Player::isAlive() {
    if(getVita()) { qDebug() << "non sono ancora morto bastardo!" << endl; return true;}
    else { qDebug() << "Player " << " è morto" << endl; return false;}
  }


  //CLASSE MOB
  Mob::Mob(QString n, int v, int m): Character(n, v, m) {}
  void Mob::info() { qDebug() << "sono Mob " << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Mob::isAlive() {
    if(getVita()) { qDebug() << "non sono ancora morto bastardo!" << endl; return true;}
    else { qDebug() << "Mob " << " è morto" << endl; return false;}
  }
