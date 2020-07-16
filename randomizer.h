#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <string>

#include "item.h"
#include "armor.h"
#include "mob.h"
#include "weapon.h"
#include "sword.h"
#include "bow.h"
#include "potion.h"
#include "magicweapon.h"

using namespace std;

//class Mob;
//class Item;
//class Armor;
//class Weapon;
//class Sword;
//class Bow;
//class Potion;
//class MagicWeapon;

/**
 * classe statica per ottenere valori oppure oggetti random
 * avendo tutti i metodi statici è possibile utilizzarla senza bisogno di istanziare un oggetto
 */
class Randomizer {
private:

    struct ScrapedInfo {
      string name;
      int lvl;
      string file;
      ScrapedInfo(string n, int l, string f): name(n), lvl(l), file(f) {}
    };

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

  static ScrapedInfo getRandomImgBow();

  static Item* getRandomItem();
  static Weapon* getRandomWeapon();
  static Sword* getRandomSword();
  static Bow* getRandomBow();
  static MagicWeapon* getRandomMagicWeapon();
  //ecc ecc per ogni arma

  static Potion* getRandomPotionMana();
  static Potion* getRandomPotionVita();

  static Armor* getRandomArmor();

  static Mob* getRandomMob();

  static string getRandomMobName();
};

#endif
