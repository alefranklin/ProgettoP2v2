#include "character.h"
#include "entity.h"
#include <iostream>
#include <vector>
using namespace std;

  //CLASSE CHARACTER
  Character::Character(QString n = "orc", int v, int m): name(n), vita(v), mana(m), Entity() { cout << "istanzio Character: " << endl; }
  QString Character::getName() { return name; }
  int Character::getVita() { return vita; }
  int Character::getMana() { return mana; }
  void Character::setDamage(int d) { vita = (vita-d >= 0) ? vita-d : 0; isAlive();}
  int Character::attacca(Character* target) { return arma->use(this, target);}

  //CLASSE PLAYER
  Player::Player(QString n, int v, int m): Character(n, v, m) {}
  void Player::save() { cout << "salvo Player " << endl; }
  void Player::info() { cout << "sono Player " << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Player::isAlive() {
    if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
    else { cout << "Player " << " è morto" << endl; return false;}
  }


  //CLASSE MOB
  Mob::Mob(int v, int m): Character(v, m) {}
  void Mob::save() { cout << "salvo Mob " << endl; }
  void Mob::info() { cout << "sono Mob " << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Mob::isAlive() {
    if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
    else { cout << "Mob " << " è morto" << endl; return false;}
  }
