#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

template<typename T>
class Container
{
public:
    friend class Iterator;
    friend class Const_Iterator;

    class Iterator {
        friend class Container;

    public:

        Iterator() = default;
        Iterator(const typename Container<T>::smartp&);
        Iterator(const Iterator&) = default;
        ~Iterator() = default;

        Iterator& operator++();                 // incremento prefisso
        Iterator& operator++(int);              // incremento postfisso

        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;

        T& operator*() const;
        T* operator->() const;

    private:
        typename Container<T>::smartp punt;
    };

    class Const_Iterator {
    public:

        Const_Iterator() = default;
        Const_Iterator(const typename Container<T>::smartp&);
        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(const Iterator&);
        ~Const_Iterator() = default;

        bool operator==(const Const_Iterator&) const;
        bool operator!=(const Const_Iterator&) const;

        Const_Iterator& operator++();
        Const_Iterator& operator++(int); //optional


        const T& operator*() const;
        const T* operator->() const;
    private:
        typename Container::smartp punt;
    };

    Container();
    Container(const Container<T>&);

    int size() const;
    bool empty() const;
    void push_back(const T&);                   // O(n)
    void push_front(const T&);                  // O(1)
    void pop_back();                            // O(n)
    void pop_front();                           // O(1)
    Iterator insert(Iterator, const T&);
    Iterator erase(Iterator);
    Iterator erase(Iterator, Iterator);
    void clear();
    void remove(const T&);

    bool operator== (const Container<T>&);
    bool operator!= (const Container<T>&);

    Container<T>& operator= (const Container<T>&);

    T& operator[](Iterator) const;
    Iterator begin();
    Iterator end();

    const T& operator[](Const_Iterator) const;
    Const_Iterator cbegin() const;
    Const_Iterator cend() const;

private:

    class nodo;
    class smartp {
    public:
        nodo* punt;

        smartp(nodo* p = 0);                    // costruttore e convertitore di tipo da nodo* a smartp
        smartp(const smartp&);                  // costruttore di copia
        ~smartp();
        smartp& operator=(const smartp&);       // assegnazione
        nodo& operator*() const;                // dereferenziazione
        nodo* operator->() const;               // accesso a membro
        bool operator==(const smartp&) const;   // uguaglianza
        bool operator!=(const smartp&) const;   // disuguaglianza
    };

    class nodo {
    public:
        nodo();
        nodo(const T&, const smartp&);
        T info;
        smartp next;
        int riferimenti;                        // contatore puntatori
        ~nodo() = default;
    };

    smartp first;
    int _size;

};

#include "container.h"

// costruttore
template<typename T>
Container<T>::Container(): first(0), _size(0) {}

// costruttore di copia
template<typename T>
Container<T>::Container(const Container<T>& c):
    first(c.first), _size(c._size) {}

// assegnazione
template<typename T>
Container<T>& Container<T>::operator=( const Container<T>& c) {
    if(this != &c) {
        first = c.first;
        _size = c._size;
    }
    return *this;
}

// size
template<typename T>
int Container<T>::size() const {
    return _size;
}

// empty
template<typename T>
bool Container<T>::empty() const {
    return _size == 0;
}

// uguaglianza
template<typename T>
bool Container<T>::operator== (const Container<T>& c) {
    if(size() != c.size()) return false;
    else {
        auto it_this = begin();
        auto it_c = c.begin();

        while(it_this != 0 && it_c != 0) {
            if( *it_this != *it_c ) return false;
            it_this++;
            it_c++;
        }
        return true;
    }
}

// disuguaglianza
template<typename T>
bool Container<T>::operator!= (const Container<T>& c) {
    return !(*this == c);
}

// push_front
template<typename T>
void Container<T>::push_front(const T& t) {
    first = new nodo(t, first);     // conversione implicita
    _size++;                        // incremento dimensione
}

// push_back
template<typename T>
void Container<T>::push_back(const T& t) {
    if(first != 0) {
        smartp aux = first;
        while(aux->next != 0) {
            aux = aux->next;
        }
        aux->next = new nodo(t, 0);
    } else first = new nodo(t, 0);
    _size++;                        // incremento dimensione
}

// pop_front
template<typename T>
void Container<T>::pop_front() {
    if(first != 0) {
        smartp aux = first;
        first = first->next;
        aux->next = 0;
        delete aux;
        _size--;                    // decremento dimensione
    }
}

// pop_back
template<typename T>
void Container<T>::pop_back() {
    if(first != 0) {
        smartp aux1 = first, aux2 = first;
        while(aux2->next != 0) {
            aux1 = aux2;
            aux2 = aux2->next;
        }
        aux1->next = 0;
        delete aux2;
        _size--;                    // decremento dimensione
    }
}

// insert
// inserisco l'elemento ella posizione immeditamente prima dell'iteratore dato
template<typename T>
typename Container<T>::Iterator Container<T>::insert(Iterator pos, const T& val) {
    smartp p = first, prec, q, nuovo;
    first = 0;

    // scorro la lista e la copio fino alla posizione da trovare
    while (p !=0 && p != pos.punt ) {
        q = new nodo(p->info, p->next);
        if (prec == 0) first = q;
        else prec->next = q;
        prec = q;
        p = p->next;
    }

    nuovo = new nodo(val, p);
    if(prec == 0) first = nuovo;
    else prec->next = nuovo;
    _size++;
    return nuovo;
}

// erase
template<typename T>
typename Container<T>::Iterator Container<T>::erase(Iterator pos) {
    smartp p = first, prec, q;
    first = 0;

    // scorro la lista e la copio fino alla posizione da trovare
    while (p !=0 && p != pos.punt ) {
        q = new nodo(p->info, p->next);class Container
{
public:
    Container();
};

        if (prec == 0) first = q;
        else prec->next = q;
        prec = q;
        p = p->next;
    }

    _size--;
    if(prec == 0) first = p->next;
    else prec->next = p->next;
    return p->next;
}

// erase range
/*
 * da clusplus.com std::list::erase
 * Iterators specifying a range within the list to be removed: [first,last).
 * i.e., the range includes all the elements between first and last,
 * including the element pointed by first but not the one pointed by last.
 *
 * return:
 * An iterator pointing to the element that followed the last element erased by the function call.
 * This is the container end if the operation erased the last element in the sequence.
 *
 */
template<typename T>
typename Container<T>::Iterator Container<T>::erase(Iterator start, Iterator end) {

    for(auto it = start; it != end; ++it)
        _size--;                // decremento size

    smartp p = first, prec, q;
    first = 0;

    // scorro la lista e la copio fino alla posizione da trovare
    while (p !=0 && p != start.punt ) {
        q = new nodo(p->info, p->next);
        if (prec == 0) first = q;
        else prec->next = q;
        prec = q;
        p = p->next;
    }

    if(prec == 0) {
        first = end.punt;
    } else prec->next = end.punt;
    return end.punt;
}

// clear
template<typename T>
void Container<T>::clear() {
    erase(begin(), end());
}

// remove
// rimuove tutti gli elementi uguali a val
template<typename T>
void Container<T>::remove(const T& val) {
    for(auto it = begin(); it != end(); ++it) {
        if(val == &dynamic_cast<T*>(it.punt->info) ) erase(it);
    }
}

template<typename T>
T& Container<T>::operator[](Iterator it) const {
    return it.punt->info;
}

// begin
template<typename T>
typename Container<T>::Iterator Container<T>::begin() {
    Iterator aux(first);
    return aux;
}

// end
template<typename T>
typename Container<T>::Iterator Container<T>::end() {
    Iterator aux(0);
    return aux;
}

template<typename T>
const T& Container<T>::operator[](Const_Iterator it) const {
    return it.punt->info;
}

// cbegin
template<typename T>
typename Container<T>::Const_Iterator Container<T>::cbegin() const {
    Const_Iterator aux(first);
    return aux;
}

// cend
template<typename T>
typename Container<T>::Const_Iterator Container<T>::cend() const {
    Const_Iterator aux(0);
    return aux;
}

/****** classe annidata iterator ******/

template<typename T>
Container<T>::Iterator::Iterator(const typename Container<T>::smartp& s): punt(s) {

}

template<typename T>
bool Container<T>::Iterator::operator==(const Iterator& i) const {
    return punt == i.punt;
}

template<typename T>
bool Container<T>::Iterator::operator!=(const Iterator& i) const {
    return punt != i.punt;
}

// incremento prefisso
template<typename T>
typename Container<T>::Iterator& Container<T>::Iterator::operator++() {
    if(punt != 0) punt = punt->next;
    return *this;
}

// incremento postfisso
template<typename T>
typename Container<T>::Iterator& Container<T>::Iterator::operator++(int) {
    Iterator aux = *this;
    if(punt != 0) punt = punt->next;
    return aux;
}

template<typename T>
T& Container<T>::Iterator::operator*() const {
    return (*punt).info;
}

template<typename T>
T* Container<T>::Iterator::operator->() const {
    return &(punt->info);
}

/****** classe annidata Const_iterator ******/

template<typename T>
Container<T>::Const_Iterator::Const_Iterator(const Container<T>::smartp& s): punt(s) {}

template<typename T>
bool Container<T>::Const_Iterator::operator==(const Const_Iterator& i) const {
    return punt == i.punt;
}

template<typename T>
bool Container<T>::Const_Iterator::operator!=(const Const_Iterator& i) const {
    return punt != i.punt;
}

// incremento prefisso
template<typename T>
typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator++() {
    if(punt != 0) {
        punt = punt->next;
    }
    return *this;
}

// incremento postfisso
template<typename T>
typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator++(int) {
    Const_Iterator aux(*this);
    if(punt != 0) punt = punt->next;
    return aux;
}

template<typename T>
const T& Container<T>::Const_Iterator::operator*() const {
    return (*punt).info;
}

template<typename T>
const T* Container<T>::Const_Iterator::operator->() const {
    return &(punt->info);
}

/****** classe annidata nodo ******/

template<typename T>
Container<T>::nodo::nodo(): riferimenti(0) {}

template<typename T>
Container<T>::nodo::nodo(const T& t, const smartp& s): info(t), next(s), riferimenti(0) {}



/************************ classe annidata smartp ******************************/

// costruttore e convertitore di tipo
template<typename T>
Container<T>::smartp::smartp(nodo* p): punt(p) {
    if(punt != 0) punt->riferimenti++;
}

// costruttore di copia
template<typename T>
Container<T>::smartp::smartp(const smartp& s): punt(s.punt) {
    if(punt) punt->riferimenti++;
}

// distruttore
template<typename T>
Container<T>::smartp::~smartp() {
    if(punt) {
        punt->riferimenti--;
        if(punt->riferimenti == 0) delete punt;
    }
}
// assegnazione
template<typename T>
typename Container<T>::smartp& Container<T>::smartp::operator=(const smartp& s) {
    if(this != &s) {
        nodo* t = punt;
        punt = s.punt;
        if(punt) punt->riferimenti++;
        if(t) {
            t->riferimenti--;
            if(t->riferimenti == 0) delete t;
        }
    }
    return *this;
}

// dereferenziazione posso fare *s.info *s.next *s.riferimenti
template<typename T>
typename Container<T>::nodo& Container<T>::smartp::operator*() const {
    return const_cast<nodo&>(*punt);
}

// dereferenziazione posso fare s->info s->next s->riferimenti
template<typename T>
typename Container<T>::nodo* Container<T>::smartp::operator->() const {
    return const_cast<nodo*>(punt);
}


// uguaglianza
template<typename T>
bool Container<T>::smartp::operator==(const smartp& s) const {
    return punt == s.punt;
}

// disuguaglianza
template<typename T>
bool Container<T>::smartp::operator!=(const smartp& s) const {
    return punt != s.punt;
}

#endif // CONTAINER_H