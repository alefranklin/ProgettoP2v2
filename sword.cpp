#include "sword.h"
#include "character.h"

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

    int i = 0;

    for(auto &elem : target) {
        danno = elem->setDamage(getDamage());
        i++;
        if(i >= range) break;

    }

    return getDamage();
}

vector<Entity::Attribute> Sword::getAttributes() const {
    vector<Attribute> att = Weapon::getAttributes();
    att.push_back(Attribute("Tipo", "Spada"));
    att.push_back(Attribute("Range", std::to_string(range)));
    return att;
}



