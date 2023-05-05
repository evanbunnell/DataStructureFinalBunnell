#ifndef LIST_H
#define LIST_H
#include "character.h"
#include <cstddef>


class List {
public:
    List();
    void insert(Character character);
    bool search(string name);
    void Delete(string name);
    void display();
    void peak();
    int size();
    void sort();
    void emplace(Character character);
    void rePrio();
private:
    struct Node {
        Character character;
        Node *next;
    };
    Node *front = NULL;
    int tank;
    int healer;
    int dps;
};

#endif // LIST_H
