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

int Armor::use(Character *owner, Character* target)
{
    return 0;
}

vector<Entity::Attribute> Armor::getAttributes() const {
    vector<Attribute> att = Item::getAttributes();
    att.push_back(Attribute("Armatura", std::to_string(armatura)));
    return att;
}

