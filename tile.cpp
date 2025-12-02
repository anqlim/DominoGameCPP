#include "tile.h"

Tile::Tile(int _left, int _right) : left(_left), right(_right) {}
bool Tile::operator==(const Tile& other) const {
    return (left == other.left && right == other.right) ||
           (left == other.right && right == other.left);
}
void Tile::swap() {
    int temp = left;
    left = right;
    right = temp;
}
void drawDots(float x, float y, int value, float k = 1) {
    Vector2 positions[7][6] = {
            {},
            {{30, 30}},
            {{15, 45}, {45, 15}},
            {{15, 45}, {30, 30}, {45, 15}},
            {{15, 15}, {15, 45}, {45, 15}, {45, 45}},
            {{15, 15}, {15, 45}, {30, 30}, {45, 15}, {45, 45}},
            {{15, 15}, {15, 30}, {45, 15}, {15, 45}, {45, 30}, {45, 45}}
    };

    for (int i = 0; i < value && i < 6; ++i) {
        int dotX = x + positions[value][i].x * k;
        int dotY = y + positions[value][i].y * k;
        DrawCircle(dotX, dotY, TILE_HEIGHT / 12 * k, PRUSSIANBLUE);
    }
}
void Tile::draw(float x, float y, float width, float height) {
    DrawRectangle(x, y - width, height, width, PAPAYAWHIP);
    DrawRectangleLines(x, y - width, height, width / 2, PRUSSIANBLUE);
    DrawRectangleLines(x, y - width + width / 2, height, width / 2, PRUSSIANBLUE);
    drawDots(x, y - width, left, (float)width / TILE_WIDTH);
    drawDots(x, y - width + width / 2, right, (float)width / TILE_WIDTH);
}
void Tile::drawTexture(float x, float y, Position position, bool isSelected, float width, float height) {
    int hash = getTileHash(left, right, isSelected);
    if (cache.find(hash) == cache.end()) return;

    Texture2D tex = cache[hash];
    y = WINDOW_HEIGHT - y;

    if (position == vertical) {
        DrawTextureEx(tex, {x, y - width}, 0, width / TILE_WIDTH,  RAYWHITE);
    }
    else {
        DrawTextureEx(tex, {x, y - height}, 90, width / TILE_WIDTH, RAYWHITE);
    }
}