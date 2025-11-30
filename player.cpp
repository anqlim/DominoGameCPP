#include "player.h"

bool Player::noSolutions(Field& field) const{
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
int Player::points() const{
    int points(0);
    Node* current = head;
    while (current) {
        points += current->tile.left + current->tile.right;
        current = current->next;
    }
    return points;
}
void Player::copy(Player& other) {
    PROFILE_SCOPE("player.copy()");
    Node* current = other.tail;
    while (current) {
        add(current->tile);
        current = current->prev;
    }
}
Node* User::clicked(float mouseX, float mouseY) {
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
void User::draw(Node* selected) {
    Node* current = head;
    int x = USER_X;
    while (current) {
        if (current != selected)
            current->tile.draw(x, USER_Y, vertical);
        else
            current->tile.drawSelected(x, USER_Y, vertical);
        x += TILE_HEIGHT + SHIFT;
        current = current->next;
    }
}
int Player::countTiles() const{
    int count(0);
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

bool match(Tile& tile, int val) {
    return tile.left == val || tile.right == val;
}
