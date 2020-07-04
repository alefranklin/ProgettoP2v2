#include "bow.h"

#include <QDebug>

Bow::Bow(string n, int d, int a):
    Item(n)
  , Weapon(n, d)
  , arrows(a)
{

}

int Bow::getArrow() const
{
    return arrows;
}

int Bow::use(Character* owner, vector<Character*> target)
{
    qDebug() << "sto usando ARCO " << endl;
    return 0;
}
