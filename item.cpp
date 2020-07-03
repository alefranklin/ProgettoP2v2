
#include <iostream>
//#include <vector>
#include <QString>
#include <QDebug>

#include "item.h"
#include "character.h"

using namespace std;

Item::Item(string n): nome(n), Entity() { qDebug() << "istanzio Item: "<< endl; }

string Item::getNome() const{ return nome; }

Item::~Item() { qDebug() << "elimino Item:" << endl; }
//questo metodo viene usato per ritornare tutti gli attributi di un oggetto
//per poterli stampare nella lista nella gui
 //vector<Attribute<T>> getAttributes() =0;

Potion::Potion(string n, int e): Item(n), effect(e) {}

int Potion::getEffect() const { return effect; }
Potion::~Potion() { qDebug() << "elimino Potion: " << endl; }
int Potion::use(Character* owner, QVector<Character*> target) { qDebug() << "sto usando Potion " << " ripristina " << effect << " salute" << endl; }
/* vector<Attribute<T>> getAttributes() {
   vector<Attribute<T>> att;
   att.push_back(Attribute("effect", &effect));
   return att;
 }*/


Weapon::Weapon(string n, int d): Item(n), damage(d) {}
Weapon::~Weapon() { qDebug() << "elimino Weapon:" << endl; }
int Weapon::getDamage() const { return damage; }
//vector<Attribute<T>> Weapon::getAttributes() {}

Sword::Sword(string n, int d, int r) :  Item(n), Weapon(n, d), range(r) {}
int Sword::getRange() const { return range; }
int Sword::use(Character* owner, QVector<Character*> target) { qDebug() << "sto usando SPADA " << endl;}


Bow::Bow(string n, int d, int a) : Weapon(n, d), arrows(a), Item(n) {}
int Bow::getArrow() const { return arrows; }
int Bow::use(Character* owner, QVector<Character*> target) { qDebug() << "sto usando ARCO " << endl;}



Magic::Magic(string n, int e, int m): Item(n), effect(e), mana(m) {}
Magic::~Magic() { qDebug() << "elimino Magic:" << endl; }
int Magic::getEffect() const { return effect; }
int Magic::getMana() const { return mana; }
//void Magic::use() { qDebug() << "sto usando Magic " << " subisci " << effect << " danno" << endl; }
//vector<Attribute<T>> Magic::getAttributes() {}


/*Melee::Melee(int d): Weapon(id, d) {}
Melee::~Melee() { qDebug() << "elimino Melee:" << endl; }
void Melee::use() { qDebug() << "sto usando Weapon Melee " << " infliggi " << getDamage() << " danno" << endl; }
void Melee::save() { qDebug() << "salvo Weapon Melee" << endl; }
//vector<Attribute<T>> Melee::getAttributes() {}

MeleeMagic::MeleeMagic(int d, int e): Melee(id, d), Magic(id, e), Item(id) {}
MeleeMagic::~MeleeMagic() { qDebug() << "elimino MeleeMagic:" << endl; }
void MeleeMagic::use() { qDebug() << "grazie alla tua arma melee magica infliggi " << getDamage() << " danno fisico e " << getEffect() << " danno magico" << endl; }
void MeleeMagic::save() { qDebug() << "salvo MeleeMagic " << endl; }
//vector<Attribute<T>> MeleeMagic::getAttributes() {}
*/


MagicWeapon::MagicWeapon(string n, int d, int e, int m): Weapon(n, d), Magic(n, e, m), Item(n) {}
MagicWeapon::~MagicWeapon() { qDebug() << "elimino MagicWeapon:" << endl; }
int MagicWeapon::use(Character* owner, QVector<Character*> target) {
  qDebug() << "Arma magica" << endl;
  if(100 >= Magic::getMana()){ //**** AGGGIORNARE CON manaPG
    //settare nuovo mana disponibile nel personaggio
    qDebug() << " + infliggi " << Weapon::getDamage()*Magic::getEffect() << " danno magico" << endl;
  }
}
//void MagicWeapon::useMana() { qDebug() << " Uso " << Magic::getMana() << " mana" << endl; }
//vector<Attribute<T>> MagicWeapon::getAttributes() {}

Armor::Armor(string n, int a): Item(n), armatura(a) {}

int Armor::getArmatura() const { return armatura; }
Armor::~Armor() { qDebug() << "elimino Armor:" << endl; }
int Armor::absorb(int danno) { return (armatura > danno) ? 0 : danno-armatura; }
//void Armor::use() { }
//vector<Attribute<T>> Armor::getAttributes() {}

