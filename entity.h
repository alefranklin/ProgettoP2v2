#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
 * classe base di tutta la gerarchia
 */
class Entity{
public:
    // struct degli attributi di un oggetto e ridefinizione operator<< e ==
    struct Attribute {
        string name;
        string val;
        Attribute(string s, string v): name(s), val(v) {}
        friend ostream& operator<<(ostream& out, const Attribute &a);
    };

    virtual vector<Attribute> getAttributes() const =0 ;

protected:
    Entity() = default;
    virtual ~Entity() = default;
};

#endif
