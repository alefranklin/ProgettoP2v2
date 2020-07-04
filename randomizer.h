#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <string>
using namespace std;

class Mob;
class Item;
class Armor;
class Weapon;
class Sword;
class Bow;
class Potion;

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

  static Item* getRandomItem();
  static Weapon* getRandomWeapon();
  static Sword* getRandomSword();
  static Bow* getRandomBow();
  //ecc ecc per ogni arma

  static Potion* getRandomPotion();

  static Armor* getRandomArmor();

  static Mob* getRandomMob();

  static string getRandomMobName();
  //static string getrandomNpcName();
};

#endif
