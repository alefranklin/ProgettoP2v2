#include "player.h"

#include "item.h"
#include "game.h"
#include "randomizer.h"

//CLASSE PLAYER
Player::Player(string n, int v, int m):
    Character(n, v, m)
{

}

Player::~Player() {
    if(getWeapon()) delete getWeapon();
    if(getArmor()) delete getArmor();
    inventory.clear();
}

/*int Player::useItem(unsigned int id, std::vector<Entity *> e) {
    //Item *i = inventoryGetItem(id);
    //if(Game::isPotion(i)) usePotion(i);
    //else exchangeWearable(i);
}*/

void Player::usePotion(Item *p) {

    p->use(this, nullptr);
    delete p;
}

void Player::equip(Item *i) {
    Item *old = nullptr;
    if( Game::isWeapon(i) )
    {
        old = setWeapon(i);
    }
    else if( Game::isArmor(i) )
    {
        old = setArmor(i);
    }
    if(old) inventory.push_front(old);
}

const Container<Item *>& Player::getInventory() const
{
    return inventory;
}

void Player::inventoryAdd(Item *i)
{
    inventory.push_front(i);
}

void Player::inventoryDelete(unsigned int id)
{
    for(auto it = inventory.begin(); it != inventory.end(); ++it) {
        if((*it)->getID() == id ) {
            Item *i = *it;
            inventory.erase(it);
            delete i;
            break;
        }
    }
}

Item *Player::inventoryGetItem(unsigned int id) {
    for(auto it = inventory.begin(); it != inventory.end(); ++it) {
        if((*it)->getID() == id ) {
            Item *i = (*it);
            inventory.erase(it);
            return (i);
        }
    }

    // se non trovo niente
    return nullptr;
}
