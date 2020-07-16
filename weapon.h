#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"
#include <string>
#include <vector>

class Weapon: virtual public Item {
private:
  int damage;
protected:
  Weapon(string n, int d);
public:
  virtual ~Weapon();
  virtual int getDamage() const;
  virtual int use(Character* owner, Character* target) = 0;

  virtual vector<Attribute> getAttributes() const;
};

#endif // WEAPON_H
