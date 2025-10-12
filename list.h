#ifndef LIST_H
#define LIST_H
#include "tile.h"

class Node {
private:
    Tile tile;
public:
    Node* prev;
    Node* next;
    Node(Tile _tile);
    void remove();
    void add(Tile& tile);
};

#endif
