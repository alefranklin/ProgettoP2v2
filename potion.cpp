#include "potion.h"

#include "character.h"

#include <QDebug>

Potion::Potion(string n, int e): Item(n), effect(e) {}

int Potion::getEffect() const { return effect; }
Potion::~Potion() { qDebug() << "elimino Potion: " << endl; }
int Potion::use(Character* owner, vector<Character *> target)
{
    qDebug() << "sto usando Potion " << " ripristina " << effect << " salute" << endl;
    return 0;
}
