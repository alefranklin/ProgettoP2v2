#ifndef BOW_H
#define BOW_H

#include "weapon.h"
#include <string>
#include <vector>

class Bow : virtual public Weapon {
private:
    int arrows;
public:
    Bow(string n, int d, int r);
    int getArrow() const;
    virtual int use(Character* owner, vector<Character*> target = vector<Character*>());
};

#endif // BOW_H
