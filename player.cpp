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
bool Player::noSolutions(Field& field) {
    Node* current = head;
    while (current) {
        if (match(current->tile, field.head->tile.left) || match(current->tile, field.tail->tile.right)) {
            return false;
        }
        current = current->next;
    }
    return true;
}
void Player::exception(Node* selected) {
    if (selected->next != nullptr)
        selected->next->prev = selected->prev;
    else
        tail = selected->prev;

    if (selected->prev != nullptr)
        selected->prev->next = selected->next;
    else
        head = selected->next;
}
int Player::points() {
    int points(0);
    Node* current = head;
    while (current) {
        points += current->tile.left + current->tile.right;
        current = current->next;
    }
    return points;
}
Node* User::clicked(float mouseX, float mouseY){
    Node* current = head;
    float x = USER_X, y = USER_Y;
    while (current != nullptr) {
        if (mouseX >= x && mouseX <= x + TILE_HEIGHT
        && mouseY >= y && mouseY <= y + TILE_WIDTH) {
            return current;
        }
        x += TILE_HEIGHT + SHIFT;
        current = current->next;
    }
    return nullptr;
}
bool match(Tile& tile, int val) {
    return tile.left == val || tile.right == val;
}
