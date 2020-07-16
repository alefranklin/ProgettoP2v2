#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <string>
#include <vector>

using namespace std; // TODO controllare se togliere

class Character;

class Item: public Entity {
private:
    static unsigned int usedID;
    unsigned int ID;
    string nome;
    string img;
protected:
    Item(string n, string img = "");
public:
    virtual ~Item();
    unsigned int getID() const;
    virtual string getNome() const;
    virtual int use(Character* owner, Character* target) = 0;

    virtual vector<Attribute> getAttributes() const;


};

#endif
