#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "character.h"
#include "container.h"
#include <string>

class Item;

class Player: public Character {
public:
  Player(string n, int v, int m);
  ~Player();
  /*
   * uso l'oggetto con ID = id se presente nell'inventario
   * ritorna 0 se usato, -1 se non trova l'item
   */
  int useItem(unsigned int id, std::vector<Entity *> e = std::vector<Entity *>());
  void usePotion(Item* p, std::vector<Entity *> e = std::vector<Entity *>());

  /* scambio o l'arma o la spada con il nuovo item in base al tipo */
  void exchangeWearable(Item *item);
  const Container<Item *> &getInventory() const;

  // aggiungo a inventario
  //void inventoryAdd(Item *i) { inventory.push_front(i); }
  //void inventoryDelete(unsigned int id);

private:
  Item *inventoryGetItem(unsigned int id);

  Container<Item*> inventory;
};

#endif // PLAYER_H
