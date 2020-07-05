#include "magicweapon.h"
#include "character.h"

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
  if(owner->getMana() >= getMana()){
      owner->useMana(getMana());
      return target->setDamageTaken(getDamage()+(getEffect()/2));
  } else {
      return target->setDamageTaken(1);
  }
}

int MagicWeapon::getDamage() const
{
    return Weapon::getDamage()+(getEffect()/2);
}

vector<Entity::Attribute> MagicWeapon::getAttributes() const {

    //TODO aggiungere attributo
    vector<Attribute> att = Weapon::getAttributes();
    vector<Attribute> att_m = Magic::getAttributes();

    att.push_back(Attribute("Tipo", "ArmaMagica"));
    //concateno
    att.insert(att.end(), att_m.begin(), att_m.end());
    return att;
}
