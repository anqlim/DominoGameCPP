#include "player.h"

Player::Player(){
    head = nullptr;
    tail = nullptr;
}

Player::~Player(){
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}