#include "magic.h"

#include <QDebug>

Magic::Magic(string n, int e, int m):
    Item(n)
  , effect(e)
  , mana(m)
{

}

Magic::~Magic()
{
    qDebug() << "elimino Magic:" << endl;
}

int Magic::getEffect() const
{
    return effect;
}

int Magic::getMana() const
{
    return mana;
}

//void Magic::use() { qDebug() << "sto usando Magic " << " subisci " << effect << " danno" << endl; }
