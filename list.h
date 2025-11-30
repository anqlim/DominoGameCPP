#ifndef LIST_H
#define LIST_H
#include "profile.h"
#include "tile.h"

class Node {
public:
    Tile tile;
    Node* prev;
    Node* next;
    Node(Tile _tile);
};

class List {
public:
    Node* head;
    Node* tail;
    List();
    ~List();
    void add(Tile tile);
};

#endif
