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

Item* Randomizer::getRandomItem() {/*chiamare casualmente o randomWeapon o randonArmor o potion o altri item istanziabili*/}

//Weapon* Randomizer::getRandomWeapon(int livello) {/*chiamare casualmente uno dei metodi sotto*/}
//static Weapon* getRandomSword(int livello);
//static Weapon* getRandomBow(int livello);
//ecc ecc per ogni arma

Item* Randomizer::getRandomPotion() {}

//static Armor* getRandomArmor(int livello);

Mob* Randomizer::getRandomMob() {}

QString Randomizer::getRandomMobName() {}
QString Randomizer::getrandomNpcName() {}
