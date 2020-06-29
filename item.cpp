#include "item.h"
#include <iostream>
#include <vector>
#include <QString>
#include "character.h"
using namespace std;

ostream& operator<<(ostream& out, const Attribute &a) {
  out << a.name + ": " + a.val;
  return out;
}

Item::Item(int i): Entity() { cout << "istanzio Item: "<< endl; }
Item::~Item() { cout << "elimino Item:" << endl; }
void use(Character* owner, Character* target = nullptr) { cout << "sto usando item " << endl; }
//questo metodo viene usato per ritornare tutti gli attributi di un oggetto
//per poterli stampare nella lista nella gui
 //vector<Attribute<T>> getAttributes() =0;

Potion::Potion(int e): Item(), effect(e) {}
Potion::~Potion() { cout << "elimino Potion: " << endl; }
void Potion::use() { cout << "sto usando Potion " << " ripristina " << effect << " salute" << endl; }
void Potion::save() { cout << "salvo Potion " << endl; }
/* vector<Attribute<T>> getAttributes() {
   vector<Attribute<T>> att;
   att.push_back(Attribute("effect", &effect));
   return att;
 }*/


Weapon::Weapon(int d): Item(), damage(d) {}
Weapon::~Weapon() { cout << "elimino Weapon:" << endl; }
int Weapon::getDamage() { return damage; }
void Weapon::save() { cout << "salvo Weapon " << endl; }
//vector<Attribute<T>> Weapon::getAttributes() {}

Sword::Sword(int d, int r) : Weapon(d), range(r), Item() {}
int Sword::getRange() { return range; }
void Sword::use() { cout << "sto usando SPADA " << endl;}


Bow::Bow(int d, int a) : Weapon(d), arrows(a), Item() {}
int Bow::getArrow() { return arrows; }
void Bow::use() { cout << "sto usando ARCO " << endl;}



Magic::Magic(int e, int m): Item(), effect(e), mana(m) {}
Magic::~Magic() { cout << "elimino Magic:" << endl; }
int Magic::getEffect() { return effect; }
int Magic::getMana() { return mana; }
//void Magic::use() { cout << "sto usando Magic " << " subisci " << effect << " danno" << endl; }
void Magic::save() { cout << "salvo Magic " << endl; }
//vector<Attribute<T>> Magic::getAttributes() {}


/*Melee::Melee(int d): Weapon(id, d) {}
Melee::~Melee() { cout << "elimino Melee:" << endl; }
void Melee::use() { cout << "sto usando Weapon Melee " << " infliggi " << getDamage() << " danno" << endl; }
void Melee::save() { cout << "salvo Weapon Melee" << endl; }
//vector<Attribute<T>> Melee::getAttributes() {}

MeleeMagic::MeleeMagic(int d, int e): Melee(id, d), Magic(id, e), Item(id) {}
MeleeMagic::~MeleeMagic() { cout << "elimino MeleeMagic:" << endl; }
void MeleeMagic::use() { cout << "grazie alla tua arma melee magica infliggi " << getDamage() << " danno fisico e " << getEffect() << " danno magico" << endl; }
void MeleeMagic::save() { cout << "salvo MeleeMagic " << endl; }
//vector<Attribute<T>> MeleeMagic::getAttributes() {}
*/


MagicWeapon::MagicWeapon(int d, int e, int m): Weapon(d), Magic(e, m), Item() {}
MagicWeapon::~MagicWeapon() { cout << "elimino MagicWeapon:" << endl; }
void MagicWeapon::use() {
  cout << "Arma magica" << endl;
  if(100 >= Magic::getMana()){ //**** AGGGIORNARE CON manaPG
    //settare nuovo mana disponibile nel personaggio
    Weapon::use();
    cout << " + infliggi " << Weapon::getDamage()*Magic::getEffect() << " danno magico" << endl;
  }
}
//void MagicWeapon::useMana() { cout << " Uso " << Magic::getMana() << " mana" << endl; }
void MagicWeapon::save() { cout << "salvo MagicWeapon " << endl; }
//vector<Attribute<T>> MagicWeapon::getAttributes() {}

Armor::Armor(int a): Item(), armatura(a) {}
Armor::~Armor() { cout << "elimino Armor:" << endl; }
int Armor::absorb(int danno) { return (armatura > danno) ? 0 : danno-armatura; }
//void Armor::use() { }
void Armor::save() { cout << "salvo Armor " << endl; }
//vector<Attribute<T>> Armor::getAttributes() {}

