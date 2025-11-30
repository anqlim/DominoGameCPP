#include "list.h"

Node::Node(Tile _tile):tile(_tile) {
    prev = nullptr;
    next = nullptr;
};

List::List() {
    head = nullptr;
    tail = nullptr;
}
List::~List() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}
void List::add(Tile tile) {
    PROFILE_SCOPE("list.add(tile)");
    if (!head) {
        head = tail = new Node(tile);
        return;
    }
    head->prev = new Node(tile);
    head->prev->next = head;
    head = head->prev;
}
