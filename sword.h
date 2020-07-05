#ifndef SWORD_H
#define SWORD_H

#include "weapon.h"
#include <string>
#include <vector>

class Sword : virtual public Weapon {
private:
    int range;
public:
    Sword(string n, int d, int r);
    int getRange() const;
    virtual int use(Character* owner, vector<Character *> target = vector<Character*>() );

    virtual vector<Attribute> getAttributes() const;
};

#endif // SWORD_H
