#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"
#include "item.h"
#include <QVector>
#include <QString>
using namespace std;

class Weapon;
class Armor;

class Character: public Entity {
private:
  QString name;
  int vita;
  int mana;
  Weapon* arma;
  Armor* armatura;
protected:
  Character(QString n, int v, int m);
public:
  QString getName();
  int getVita();
  int getMana();
  void setDamage(int d);
  virtual bool isAlive() =0;
  virtual void info() =0;

  virtual ~Character();


   /*
   mini modello di come funziona il sistema di danno e benefici

  int = player.attacca(enemies)

  //ritorna danno inflitto
  int attacca {
    return arma.use(this, enemies)
              {
                this.%crtici_giocatore
                  ememies.faidanno(danno arma + %critici_giocatore)
                          {
                              int armatura.absorb(danno)
                          }
              }
  }

  mob.attacca(Charxter player)
  */
  virtual int attacca(QVector<Character*> target);

};

class Player: public Character {
public:
  Player(QString n, int v, int m);
  void info();
  bool isAlive();
};

class Mob: public Character {
public:
  Mob(QString n, int v, int m);
  void info();
  bool isAlive();
};

#endif
