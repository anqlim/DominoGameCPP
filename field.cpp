#include "field.h"
Field::Field(){
    head = nullptr;
    tail = nullptr;
}

Field::~Field(){
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}