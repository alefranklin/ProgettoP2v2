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
 int absorb(int danno);
 virtual int use(Character* owner, vector<Character*> target = vector<Character*>() );
};

#endif // ARMOR_H
