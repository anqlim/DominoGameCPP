#include "list.h"

Node::Node(Tile _tile):tile(_tile){
    prev = nullptr;
    next = nullptr;
};

void Node::add(Tile& tile){
    Node* node = new Node(tile);
    prev = node;
    node->next = this;
}

List::List(){
    head = nullptr;
    tail = nullptr;
}
List::~List(){
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

