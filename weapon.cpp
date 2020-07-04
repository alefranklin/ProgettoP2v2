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
