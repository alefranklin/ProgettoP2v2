#include "entity.h"

ostream& operator<<(ostream& out, const Entity::Attribute &a) {
  out << a.name + ": " + a.val;
  return out;
}
