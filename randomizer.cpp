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
    int i = randomNumberBetween(1,4);

    switch (i) {
        case 1: return getRandomWeapon(); break;
        case 2: return getRandomPotionMana(); break;
        case 3: return getRandomPotionVita(); break;
        case 4: return getRandomArmor(); break;
        default: return getRandomPotionMana(); break;
    }
}

Weapon* Randomizer::getRandomWeapon()
{/*chiamare casualmente uno dei metodi sotto*/
    int i = randomNumberBetween(1,3);

    switch (i) {
        case 1: return getRandomBow(); break;
        case 2: return getRandomSword(); break;
        case 3: return getRandomMagicWeapon(); break;
        default: return getRandomSword(); break;
    }
}

//TODO randomizzare i nomi

MagicWeapon* Randomizer::getRandomMagicWeapon()
{
    return new MagicWeapon("Bastone della morte", randomNumberBetween(2,9), randomNumberBetween(2,8), randomNumberBetween(2,5));
}

Bow* Randomizer::getRandomBow()
{
    return new Bow("Arco di legno", randomNumberBetween(2,8), randomNumberBetween(2,8));
}

Sword* Randomizer::getRandomSword()
{
    return new Sword("Spada di legno", randomNumberBetween(2,8), 1);
}

Armor* Randomizer::getRandomArmor()
{
    return new Armor("Armatura", randomNumberBetween(2,7));
}

Potion* Randomizer::getRandomPotionMana()
{
    return new Potion("Pozione", randomNumberBetween(10,20), randomNumberBetween(0,1), true);
}

Potion* Randomizer::getRandomPotionVita()
{
    return new Potion("Pozione", randomNumberBetween(10,20), true, randomNumberBetween(0,1));
}

//static Armor* getRandomArmor(int livello);

Mob* Randomizer::getRandomMob()
{
    return new Mob(getRandomMobName(), randomNumberBetween(10,20), randomNumberBetween(7,15));
}

//TODO mettere nomi random
string Randomizer::getRandomMobName() { return "Orco"; }
//string Randomizer::getrandomNpcName() { return ""; }
