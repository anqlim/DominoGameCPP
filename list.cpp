#include "list.h"

Node::Node(Tile _tile):tile(_tile){};

void Node::remove() {
    if (next != nullptr) next->prev = prev;
    if (prev != nullptr) prev->next = next;
    delete this;
}

void Node::add(Tile& tile){
    Node* node = new Node(tile);
    prev = node;
    node->next = this;
}
