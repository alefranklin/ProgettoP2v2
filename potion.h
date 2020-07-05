#ifndef POTION_H
#define POTION_H

#include "item.h"
#include <string>
#include <vector>


class Potion: public Item {
private:
 int effect;

 /*se impostati recuperano l'effetto di vita e mana*/
 bool vita;
 bool mana;
public:
 Potion(string n, int e);
 int getEffect() const;
 virtual ~Potion();
 virtual int use(Character* owner, vector<Character*> target = vector<Character*>());

 virtual vector<Attribute> getAttributes() const;
};

#endif // POTION_H
