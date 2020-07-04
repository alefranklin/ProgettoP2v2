#include "player.h"

#include "item.h"
#include "sword.h"

//CLASSE PLAYER
Player::Player(string n, int v, int m):
    Character(n, v, m)
{
    Item *s =  new Sword("ciao", 100, 1);
    inventory.push_back( s );
}

Player::~Player() {
    if(getWeapon()) delete getWeapon();
    if(getArmor()) delete getArmor();
}

int Player::useItem(unsigned int id, std::vector<Entity *> e) {
    Item *i = inventoryGetItem(id);
    //if(Game::isPotion(i)) usePotion(i);
    //else exchangeWearable(i);
}

void Player::usePotion(Item *p, std::vector<Entity *> e) {
    //Character *c = dynamic_cast<Character*>(this);
    //p->use(c, e);
    //delete p;
}

void Player::exchangeWearable(Item *item) {
    /*if(Game::isWeapon(item)) {
        Weapon *w = dynamic_cast<Weapon *>(item);
        setWeapon(w);
    }
    if(Game::isArmor(item)) {

    }*/

}

const Container<Item *>& Player::getInventory() const
{
    //return inventory;
}

Item *Player::inventoryGetItem(unsigned int id) {

}
