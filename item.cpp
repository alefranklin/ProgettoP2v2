
#include <iostream>
//#include <vector>
#include <QString>
#include <QDebug>

#include "item.h"
#include "character.h"

using namespace std;

Item::Item(int i): Entity() { qDebug() << "istanzio Item: "<< endl; }
Item::~Item() { qDebug() << "elimino Item:" << endl; }

QString Item::getNome() const{
    return nome;
}
//questo metodo viene usato per ritornare tutti gli attributi di un oggetto
//per poterli stampare nella lista nella gui
 //vector<Attribute<T>> getAttributes() =0;

Potion::Potion(int e): Item(), effect(e) {}
Potion::~Potion() { qDebug() << "elimino Potion: " << endl; }

int Potion::getEffect() const{
    return effect;
}
int Potion::use(Character* owner, QVector<Character*> target) { qDebug() << "sto usando Potion " << " ripristina " << effect << " salute" << endl; }
/* vector<Attribute<T>> getAttributes() {
   vector<Attribute<T>> att;
   att.push_back(Attribute("effect", &effect));
   return att;
 }*/


Weapon::Weapon(int d): Item(), damage(d) {}
Weapon::~Weapon() { qDebug() << "elimino Weapon:" << endl; }
int Weapon::getDamage() const{ return damage; }
//vector<Attribute<T>> Weapon::getAttributes() {}

Sword::Sword(int d, int r) : Weapon(d), range(r), Item() {}
int Sword::getRange() const{ return range; }
int Sword::use(Character* owner, QVector<Character*> target) { qDebug() << "sto usando SPADA " << endl;}


Bow::Bow(int d, int a) : Weapon(d), arrows(a), Item() {}
int Bow::getArrow() const{ return arrows; }
int Bow::use(Character* owner, QVector<Character*> target) { qDebug() << "sto usando ARCO " << endl;}



Magic::Magic(int e, int m): Item(), effect(e), mana(m) {}
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


MagicWeapon::MagicWeapon(int d, int e, int m): Weapon(d), Magic(e, m), Item() {}
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

Armor::Armor(int a): Item(), armatura(a) {}
Armor::~Armor() { qDebug() << "elimino Armor:" << endl; }
int Armor::absorb(int danno) { return (armatura > danno) ? 0 : danno-armatura; }
//void Armor::use() { }
//vector<Attribute<T>> Armor::getAttributes() {}

