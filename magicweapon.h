#ifndef MAGICWEAPON_H
#define MAGICWEAPON_H

#include "weapon.h"
#include "magic.h"
#include <string>
#include <vector>

class MagicWeapon: virtual public Weapon, virtual public Magic {
public:
  MagicWeapon(string n, int d, int e, int m);
  virtual ~MagicWeapon();
  virtual int use(Character* owner, vector<Character*> target = vector<Character*>());
};

#endif // MAGICWEAPON_H
