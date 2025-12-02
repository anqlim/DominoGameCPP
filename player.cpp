#include "player.h"


bool match(Tile& tile, int val) {
    return tile.left == val || tile.right == val;
}

bool Player::noSolutions(Field& field) const {
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
int Player::countTiles() const{
    int count(0);
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
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
    PROFILE_SCOPE("user.draw()");
    Node* current = head;
    int x = USER_X;
    while (current) {
        current->tile.drawTexture(x, USER_Y, vertical, current == selected);
        x += TILE_HEIGHT + SHIFT;
        current = current->next;
    }
}

