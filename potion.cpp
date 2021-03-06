#include "potion.h"

#include "character.h"

#include <QDebug>

Potion::Potion(string n, int e, bool v, bool m): Item(n), effect(e), vita(v), mana(m) {}

int Potion::getEffect() const { return effect; }
Potion::~Potion() { qDebug() << "elimino Potion: " << endl; }

int Potion::use(Character* owner, Character* target)
{
    target = nullptr; //evito il warning "unused parameter target"

    if(mana) owner->addMana(effect);
    if(vita) owner->addVita(effect);

    return effect;
}

vector<Entity::Attribute> Potion::getAttributes() const {
    vector<Attribute> att = Item::getAttributes();
    att.push_back(Attribute("Tipo", "Pozione"));
    att.push_back(Attribute("Effetto", std::to_string(effect)));
    att.push_back(Attribute("Vita", ((vita) ? "si" : "no") ));
    att.push_back(Attribute("Mana", ((mana) ? "si" : "no") ));
    return att;
}
