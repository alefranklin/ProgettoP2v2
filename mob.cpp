#include "mob.h"

Mob::Mob(string n, int v, int m): Character(n, v, m) {

}

void Mob::info() {

}

bool Mob::isAlive() {
    if(getVita()) { return true; }
    else { return false; }
}
