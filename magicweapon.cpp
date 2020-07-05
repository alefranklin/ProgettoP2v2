#include "magicweapon.h"

#include <QDebug>

MagicWeapon::MagicWeapon(string n, int d, int e, int m):
    Item(n),
    Weapon(n, d),
    Magic(n, e, m)
{

}

MagicWeapon::~MagicWeapon()
{
    qDebug() << "elimino MagicWeapon:" << endl;
}

int MagicWeapon::use(Character* owner, Character* target)
{
  qDebug() << "Arma magica" << endl;
  if(100 >= Magic::getMana()){ //**** AGGGIORNARE CON manaPG
    //settare nuovo mana disponibile nel personaggio
    qDebug() << " + infliggi " << Weapon::getDamage()*Magic::getEffect() << " danno magico" << endl;
  }
}

vector<Entity::Attribute> MagicWeapon::getAttributes() const {
    vector<Attribute> att = Weapon::getAttributes();
    vector<Attribute> att_m = Magic::getAttributes();
    //concateno
    att.insert(att.end(), att_m.begin(), att_m.end());
    return att;
}
