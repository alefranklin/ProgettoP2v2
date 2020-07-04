#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"
#include <vector>
#include <string>
using namespace std;

class Item;

class Character: public Entity {
private:
  static const int maxVita;
  static const int maxMana;
  string name;
  int vita;
  int mana;
  Item* arma;
  Item* armatura;
protected:
  Character(string n, int v, int m);
public:
  virtual ~Character() = default;
  virtual string getName();
  virtual int getVita() const;
  virtual void setVita(int v);
  virtual void addVita(int v);
  virtual int getMana() const;
  virtual void setMana(int m);
  virtual void addMana(int m);
  virtual void setDamage(int d);
  virtual Item* getWeapon();

  /*ritorna la vecchia arma */
  virtual Item* setWeapon(Item *w);
  virtual Item* getArmor();

  /* ritorna la vecchia armatura */
  virtual Item* setArmor(Item *a);
  virtual bool isAlive();


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
  virtual int attacca(vector<Character*> target);

};

#endif
