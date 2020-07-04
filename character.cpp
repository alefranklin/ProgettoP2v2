#include "character.h"

#include <QDebug>
#include "sword.h"
#include "armor.h"
using namespace std;

const int Character::maxVita = 500;
const int Character::maxMana = 250;

//CLASSE CHARACTER
Character::Character(string n, int v, int m):
    Entity()
  , name(n)
  , vita(v)
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

void Character::setVita(int v) {
    if(v < maxVita) vita = v;
    else vita = maxVita;
}

void Character::addVita(int v) {
    if( vita+v < maxVita) vita += v;
    else vita = maxVita;
}

int Character::getMana() const
{
    return mana;
}

void Character::setMana(int m) {
    if(m < maxMana) mana = m;
    else mana = maxMana;
}

void Character::addMana(int m) {
    if( mana+m < maxMana) mana += m;
    else mana = maxMana;
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

