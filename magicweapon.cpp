#include "magicweapon.h"
#include "character.h";

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
  qDebug() << "USO ARMA MAGICA" << endl;
  if(owner->getMana() > getMana()){
      owner->useMana(getMana());
      return target->setDamageTaken(getDamage()*(getEffect()/10));
  } else {
      return 0;
  }
}

vector<Entity::Attribute> MagicWeapon::getAttributes() const {

    //TODO aggiungere attributo
    vector<Attribute> att = Weapon::getAttributes();
    vector<Attribute> att_m = Magic::getAttributes();

    //concateno
    att.insert(att.end(), att_m.begin(), att_m.end());
    return att;
}
