#include "armor.h"

#include <QDebug>

Armor::Armor(string n, int a):
    Item(n)
  , armatura(a)
{

}

int Armor::getArmatura() const
{
    return armatura;
}

Armor::~Armor()
{
    qDebug() << "elimino Armor:" << endl;
}

int Armor::absorb(int danno)
{
    return (armatura > danno) ? 0 : danno-armatura;
}

int Armor::use(Character *owner, vector<Character *> target)
{
    return 0;
}

