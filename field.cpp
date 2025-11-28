#include "field.h"

Field Field::copy() {
    Field copy;
    Node *current = tail;
    while (current) {
        if (copy.head) {
            copy.head->add(current->tile);
            copy.head = copy.head->prev;
        }
        else {
            Node* newNode = new Node(current->tile);
            copy.head = newNode;
            copy.tail = newNode;
        }
        current = current->prev;
    }
    return copy;
}

void Field::draw() {
    Node* current = head;
    float count(0);
    while (current) {
        if (current->tile.left == current->tile.right) count += 0.5;
        else count += 1;
        current = current->next;
    }

    float x, y, width, height;
    if (TILE_WIDTH * count + 100 <= WINDOW_WIDTH) {
        width = TILE_WIDTH;
        height = TILE_HEIGHT;
    }
    else {
        width = (WINDOW_WIDTH - 100) / count;
        height = width / 2;
    }
    x = WINDOW_WIDTH / 2 - count * width / 2;
    y = WINDOW_HEIGHT / 2 - width / 2;

    current = head;
    while (current) {
        if (current->tile.left == current->tile.right) {
            current->tile.draw(x, y - height / 2, vertical, width, height);
            x += height;
        }
        else {
            current->tile.draw(x, y, horizontal, width, height);
            x += width;
        }
        current = current->next;
    }

}