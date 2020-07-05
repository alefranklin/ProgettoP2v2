#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"
#include <vector>
#include <string>
using namespace std;

class Item;

class Character: public Entity {
private:
  string name;
  int vita;
  int vitaMax;
  int manaMax;
  int mana;
  Item* arma;
  Item* armatura;
protected:
  Character(string n, int v, int m);
public:
  virtual ~Character() = default;
  virtual string getName();
  virtual int getVita() const;
  virtual int getVitaMax() const;
  virtual void setVita(int v);
  virtual void addVita(int v);
  virtual int getMana() const;
  virtual int getManaMax() const;
  virtual void setMana(int m);
  virtual void addMana(int m);
  virtual void setDamage(int d);
  virtual Item* getWeapon();

  /* prendo l'arma e metto nullptr */
  virtual Item* removeWeapon();

  /*ritorna la vecchia arma */
  virtual Item* setWeapon(Item *w);
  virtual Item* getArmor();

  /*prendo l'armatura e metto nullptr */
  virtual Item* removeArmor();

  /* ritorna la vecchia armatura */
  virtual Item* setArmor(Item *a);
  virtual bool isAlive();

  virtual vector<Entity::Attribute> getAttributes() const;


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
