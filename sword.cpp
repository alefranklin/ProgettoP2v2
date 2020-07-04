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

