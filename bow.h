#ifndef BOW_H
#define BOW_H

#include "weapon.h"
#include <string>
#include <vector>

class Bow : virtual public Weapon {
private:
    int arrows;
public:
    Bow(string n, string img, int d, int r);
    int getArrow() const;
    virtual int use(Character* owner, Character* target = nullptr);

    virtual vector<Attribute> getAttributes() const;
    void useArrow();
};

#endif // BOW_H
