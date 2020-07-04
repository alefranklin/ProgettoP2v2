#ifndef POTION_H
#define POTION_H

#include "item.h"
#include <string>
#include <vector>


class Potion: public Item {
private:
 int effect;
public:
 Potion(string n, int e);
 int getEffect() const;
 virtual ~Potion();
 virtual int use(Character* owner, vector<Character*> target = vector<Character*>());
};

#endif // POTION_H
