#include "weapon.h"

#include <QDebug>

Weapon::Weapon(string n, int d): Item(n), damage(d)
{

}

Weapon::~Weapon()
{
    qDebug() << "elimino Weapon:" << endl;
}

int Weapon::getDamage() const
{
    return damage;
}

vector<Entity::Attribute> Weapon::getAttributes() const {
    vector<Attribute> att = Item::getAttributes();
    att.push_back(Attribute("Danno", std::to_string(damage)));
    return att;
}
