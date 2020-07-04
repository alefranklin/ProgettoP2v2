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

int MagicWeapon::use(Character* owner, vector<Character*> target)
{
  qDebug() << "Arma magica" << endl;
  if(100 >= Magic::getMana()){ //**** AGGGIORNARE CON manaPG
    //settare nuovo mana disponibile nel personaggio
    qDebug() << " + infliggi " << Weapon::getDamage()*Magic::getEffect() << " danno magico" << endl;
  }
}
