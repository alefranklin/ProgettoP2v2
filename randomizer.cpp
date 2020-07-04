#include "randomizer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

unsigned int Randomizer::seed = 1; //valore di default di srand


unsigned int Randomizer::setup() {
  setSeed(time(NULL));
  return getSeed();
}  //funzione pronta

unsigned int Randomizer::getSeed() { return seed; }  //funzione pronta
void Randomizer::setSeed(unsigned int s) { seed = s; srand(s); } //funzione pronta


int Randomizer::randomNumberBetween(int min, int max) {
  return min+(rand()%(max-min+1));
}

Item* Randomizer::getRandomItem()
{/*chiamare casualmente o randomWeapon o randonArmor o potion o altri item istanziabili*/
    int i = randomNumberBetween(1,3);

    switch (i) {
        case 1: return getRandomWeapon(); break;
        case 2: return getRandomPotion(); break;
        case 3: return getRandomArmor(); break;
        default: return getRandomPotion(); break;
    }
}

Weapon* Randomizer::getRandomWeapon()
{/*chiamare casualmente uno dei metodi sotto*/
    int i = randomNumberBetween(1,2);

    switch (i) {
        case 1: return getRandomBow(); break;
        case 2: return getRandomSword(); break;
        default: return getRandomSword(); break;
    }
}

//TODO randomizzare i nomi

Bow* Randomizer::getRandomBow()
{
    return new Bow("Spada di legno", randomNumberBetween(2,8), randomNumberBetween(2,8));
}

Sword* Randomizer::getRandomSword()
{
    return new Sword("Spada di legno", randomNumberBetween(2,8), 1);
}

Armor* Randomizer::getRandomArmor()
{
    return new Armor("Armatura", randomNumberBetween(2,7));
}

Potion* Randomizer::getRandomPotion()
{
    return new Potion("Pozione", randomNumberBetween(1,2));
}

//static Armor* getRandomArmor(int livello);

Mob* Randomizer::getRandomMob()
{
    return new Mob("Orco", randomNumberBetween(10,20), randomNumberBetween(0,5));
}

QString Randomizer::getRandomMobName() {}
QString Randomizer::getrandomNpcName() {}
