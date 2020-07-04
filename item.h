#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <string>
#include <vector>

using namespace std; // TODO controllare se togliere

class Character;

class Item: public Entity {
private:
  static unsigned int usedID;
  unsigned int ID;
  string nome;
protected:
  Item(string n);
public:
  virtual ~Item();
  unsigned int getID() const;
  virtual string getNome() const;
  virtual int use(Character* owner, vector<Character*> target) = 0;
};

#endif
