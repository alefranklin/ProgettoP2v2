#ifndef MAGIC_H
#define MAGIC_H

#include "item.h"
#include <string>
#include <vector>

class Magic: virtual public Item {
private:
  int effect;
  int mana;
protected:
  Magic(string n, int e, int m);
//public:
  virtual ~Magic();
  int getEffect() const;
  int getMana() const;
  virtual int use(Character* owner, Character* target = nullptr) = 0;

  virtual vector<Attribute> getAttributes() const;
};

#endif // MAGIC_H
