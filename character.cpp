#include "character.h"

#include <QDebug>
#include "sword.h"
#include "armor.h"
using namespace std;

//CLASSE CHARACTER
Character::Character(string n, int v, int m):
    Entity()
  , name(n)
  , vita(v)
  , vitaMax(v)
  , manaMax(m)
  , mana(m)

{
    arma = new Sword("nullptr", 100, 1);
    armatura = new Armor("ARMATURA GROSSSA", 70);
    qDebug() << "istanzio Character: ";
}

string Character::getName()
{
    return name;
}

int Character::getVita() const
{
    return vita;
}

int Character::getVitaMax() const
{
    return vitaMax;
}

int Character::getManaMax() const
{
    return manaMax;
}

void Character::setVita(int v) {
    if(v < vitaMax) vita = v;
    else vita = vitaMax;
}

void Character::addVita(int v) {
    if( vita+v < vitaMax) vita += v;
    else vita = vitaMax;
}

int Character::getMana() const
{
    return mana;
}

void Character::setMana(int m) {
    if(m < manaMax) mana = m;
    else mana = manaMax;
}

void Character::addMana(int m) {
    if( mana+m < manaMax) mana += m;
    else mana = manaMax;
}

void Character::setDamage(int d)
{
    vita = (vita-d >= 0) ? vita-d : 0;
    //isAlive();
}

Item* Character::getWeapon()
{
    return arma;
}

Item *Character::setWeapon(Item *w) {
    if(w) {
        Item *aus = arma;
        arma = w;
        return aus;
    } else return nullptr;
}

Item* Character::getArmor()
{
    return armatura;
}

Item* Character::setArmor(Item *a) {
    if(a) {
        Item *aus = armatura;
        armatura = a;
        return aus;
    } else return nullptr;
}

bool Character::isAlive() {
    if(getVita()) return true;
    else return false;

}

int Character::attacca(vector<Character *> target)
{
    return arma->use(this, target);
}

