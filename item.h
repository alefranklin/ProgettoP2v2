#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <iostream>
#include <vector>
#include <QString>
#include "character.h"
using namespace std;

class Character;

// struct degli attributi di un oggetto e ridefinizione operator<< e ==
struct Attribute {
  QString name;
  QString val;
  Attribute(QString s, QString v): name(s), val(v) {}
  friend ostream& operator<<(ostream& out, const Attribute &a);

  //se dovessero servire
  bool operator==(const Attribute &a) {
    return ( name==a.name && val==a.val);
  }
  bool operator!=(const Attribute &a) {
    return !(*this == a);
  }
};

class Item: public Entity {
private:
  QString nome;
protected:
  Item(int i = 0);
public:
  virtual ~Item();
  virtual void use(Character* owner, Character* target = nullptr);
  virtual void save() = 0;
  //questo metodo viene usato per ritornare tutti gli attributi di un oggetto
  //per poterli stampare nella lista nella gui
  //virtual vector<Attribute<T>> getAttributes() =0;
};


class Potion: public Item {
private:
 int effect;
public:
 Potion(int e);
 virtual ~Potion();
 virtual void use();
 virtual void save();
 /*
 virtual vector<Attribute<T>> getAttributes() {
   vector<Attribute<T>> att;
   att.push_back(Attribute("effect", &effect));
   return att;
 }*/
};


class Weapon: virtual public Item {
private:
  int damage;
protected:
  Weapon(int d);
public:
  virtual ~Weapon();
  virtual int getDamage();
  virtual int use(Character* owner, Character* target = nullptr);
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}
};

class Sword : virtual public Weapon {
  private:
    int range;
  public:
    Sword(int d, int r);
    int getRange();
    //virtual void use();

    /*
    ... getattribute() {
      //concateni i vettori
      return vettore[renge] + weapon::getattribute()
    }
    */
};

class Bow : virtual public Weapon {
  private:
    int arrows;
  public:
    Bow(int d, int r);
    int getArrow();
    //virtual void use();
};

class Magic: virtual public Item {
private:
  int effect;
  int mana;
protected:
  Magic(int e, int m);
public:
  virtual ~Magic();
  int getEffect();
  int getMana();
  //virtual void use();
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}

};


class MagicWeapon: virtual public Weapon, virtual public Magic {
public:
  MagicWeapon(int d, int e, int m);
  virtual ~MagicWeapon();
  virtual void use();
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}
};

class Armor: virtual public Item {
private:
 int armatura;
public:
 Armor(int a);
 virtual ~Armor();
 virtual int absorb(int danno);
 //virtual void use();
 virtual void save();
 //virtual vector<Attribute<T>> getAttributes() {}
};

#endif
