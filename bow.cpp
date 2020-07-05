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

int Bow::use(Character* owner, Character* target)
{
    qDebug() << "sto usando ARCO " << endl;
    return 0;
}

vector<Entity::Attribute> Bow::getAttributes() const {
    vector<Attribute> att = Weapon::getAttributes();
    att.push_back(Attribute("Tipo", "Arco"));
    att.push_back(Attribute("Frecce", std::to_string(arrows)));
    return att;
}
