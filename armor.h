#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"
#include <string>
#include <vector>

class Armor: virtual public Item {
private:
    int armatura;
public:
    Armor(string n, int a);

    int getArmatura() const;

    virtual ~Armor();
    virtual int absorb(int danno);
    virtual int use(Character* owner, Character* target = nullptr );

    vector<Attribute> getAttributes() const;
};

#endif // ARMOR_H
