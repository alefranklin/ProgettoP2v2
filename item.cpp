#include "item.h"
#include "character.h"

#include <iostream>
#include <QDebug>
using namespace std;

unsigned int Item::usedID = 0;

Item::Item(string n, string img):
    Entity()
  , nome(n)
  , img(img)
{
    ID = usedID;
    usedID++;
    qDebug() << "istanzio Item: "<< endl;
}

unsigned int Item::getID() const
{
    return ID;
}

string Item::getNome() const
{
    return nome;
}

vector<Entity::Attribute> Item::getAttributes() const {
    vector<Attribute> att;
    att.push_back(Attribute("ID", to_string(ID)));
    att.push_back(Attribute("Nome", nome));
    att.push_back(Attribute("Immagine", img));
    return att;
}

Item::~Item()
{
    qDebug() << "elimino Item:" << endl;
}



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

