#ifndef MOB_H
#define MOB_H

#include "character.h"
#include <string>

class Mob: public Character {
public:
  Mob(string n, int v, int m);
  void info();
  bool isAlive();
};

#endif // MOB_H
