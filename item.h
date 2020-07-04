#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <iostream> // TODO da togliere
#include <QVector>
#include <QString>
#include "character.h"
using namespace std; // TODO controllare se togliere

class Character;

//// struct degli attributi di un oggetto e ridefinizione operator<< e ==
//struct Attribute {
//  QString name;
//  QString val;
//  Attribute(QString s, QString v): name(s), val(v) {}
//  friend ostream& operator<<(ostream& out, const Attribute &a);

//  //se dovessero servire
//  bool operator==(const Attribute &a) {
//    return ( name==a.name && val==a.val);
//  }
//  bool operator!=(const Attribute &a) {
//    return !(*this == a);
//  }
//};

class Item: public Entity {
private:
  unsigned int usedID;
  unsigned int ID;
  string nome;
protected:
  Item(string n);
public:
  unsigned int getID() const;
  virtual string getNome() const;
  virtual ~Item();
  virtual int use(Character* owner, QVector<Character*> target) = 0;
  

  //questo metodo viene usato per ritornare tutti gli attributi di un oggetto
  //per poterli stampare nella lista nella gui
  //virtual vector<Attribute<T>> getAttributes() =0;
};


class Potion: public Item {
private:
 int effect;
public:
 Potion(string n, int e);
 int getEffect() const;
 virtual ~Potion();
 virtual int use(Character* owner, QVector<Character*> target = QVector<Character*>());
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
  Weapon(string n, int d);
public:
  virtual ~Weapon();
  virtual int getDamage() const;
  virtual int use(Character* owner, QVector<Character*> target) = 0;
  
  //virtual vector<Attribute<T>> getAttributes() {}
};

class Sword : virtual public Weapon {
  private:
    int range;
  public:
    Sword(string n, int d, int r);
    int getRange() const;
    virtual int use(Character* owner, QVector<Character*> target = QVector<Character*>() );
    
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
    Bow(string n, int d, int r);
    int getArrow() const;
    virtual int use(Character* owner, QVector<Character*> target = QVector<Character*>());
    //virtual void use();
};

class Magic: virtual public Item {
private:
  int effect;
  int mana;
protected:
  Magic(string n, int e, int m);
public:
  virtual ~Magic();
  int getEffect() const;
  int getMana() const;
  virtual int use(Character* owner, QVector<Character*> target = QVector<Character*>()) = 0;
  
  //virtual void use();
  //virtual vector<Attribute<T>> getAttributes() {}

};


class MagicWeapon: virtual public Weapon, virtual public Magic {
public:
  MagicWeapon(string n, int d, int e, int m);
  virtual ~MagicWeapon();
  virtual int use(Character* owner, QVector<Character*> target = QVector<Character*>());
  
  //virtual vector<Attribute<T>> getAttributes() {}
};

class Armor: virtual public Item {
private:
 int armatura;
public:
 Armor(string n, int a);

 int getArmatura() const;

 virtual ~Armor();
 int absorb(int danno);
 //virtual vector<Attribute<T>> getAttributes() {}
 virtual int use(Character* owner, QVector<Character*> target){};
};

#endif
