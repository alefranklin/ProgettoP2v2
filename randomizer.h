#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "item.h"
#include "character.h"
#include <string>
#include <QString>
using namespace std;

struct ScrapedInfo {
  QString name;
  int lvl;
  QString file;
  ScrapedInfo(QString n, int l, QString f): name(n), lvl(l), file(f) {}
};


/**
 * classe statica per ottenere valori oppure oggetti random
 * avendo tutti i metodi statici è possibile utilizzarla senza bisogno di istanziare un oggetto
 */
class Randomizer {
private:
  static unsigned int seed;

  //static vettore da definire constructVectorSword()
  //static vettore da definire constructVectorBow()
  //ecc
public:
  // queste 3 funzioni permettono di avere il controllo sulla generazione dei numeri casuali
  static unsigned int setup();

  static unsigned int getSeed();
  static void setSeed(unsigned int s);


  static int randomNumberBetween(int min = 0, int max = 1);

  static Item* getRandomItem();
  static Weapon* getRandomWeapon();
  static Sword* getRandomSword();
  static Bow* getRandomBow();
  //ecc ecc per ogni arma

  static Potion* getRandomPotion();

  static Armor* getRandomArmor();

  static Mob* getRandomMob();

  static QString getRandomMobName();
  static QString getrandomNpcName();
};

#endif
