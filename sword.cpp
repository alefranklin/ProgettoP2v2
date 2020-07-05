#include "sword.h"

#include <QDebug>

Sword::Sword(string n, int d, int r) :
    Item(n)
  , Weapon(n, d)
  , range(r)
{

}

int Sword::getRange() const
{
    return range;
}

int Sword::use(Character* owner, vector<Character*> target)
{
    qDebug() << "sto usando SPADA " << endl;
    return 0;
}

vector<Entity::Attribute> Sword::getAttributes() const {
    vector<Attribute> att = Weapon::getAttributes();
    att.push_back(Attribute("Tipo", "Spada"));
    att.push_back(Attribute("Range", std::to_string(range)));
    return att;
}

