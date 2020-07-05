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

vector<Entity::Attribute> Magic::getAttributes() const {
    vector<Attribute> att = Item::getAttributes();
    att.push_back(Attribute("Effetto", std::to_string(effect)));
    att.push_back(Attribute("Mana", std::to_string(mana)));
    return att;
}

//void Magic::use() { qDebug() << "sto usando Magic " << " subisci " << effect << " danno" << endl; }
