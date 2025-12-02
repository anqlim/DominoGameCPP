#include "field.h"

void Field::copy(Field& other) {
    Node* current = other.tail;
    while (current) {
        add(current->tile);
        current = current->prev;
    }
}
void Field::draw() {
    PROFILE_SCOPE("field.draw()");
    Node* current = head;
    float count(0);
    while (current) {
        if (current->tile.left == current->tile.right) count += 0.5;
        else count++;
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
            current->tile.drawTexture(x, y - height / 2, vertical, false, width, height);
            x += height;
        }
        else {
            current->tile.drawTexture(x + width + 1, y, horizontal, false, width, height);
            x += width;
        }
        current = current->next;
    }

}