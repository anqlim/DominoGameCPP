#include "tile.h"
#include "raylib.h"
#include "parameters.h"

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
void drawDots(float x, float y, int value, Position position, float k = 1) {
    Vector2 positions[7][6] = {
            {},
            {{30, 30}},
            {{15, 15}, {45, 45}},
            {{15, 15}, {30, 30}, {45, 45}},
            {{15, 15}, {15, 45}, {45, 15}, {45, 45}},
            {{15, 15}, {15, 45}, {30, 30}, {45, 15}, {45, 45}},
            {{15, 15}, {30, 15}, {45, 15}, {15, 45}, {30, 45}, {45, 45}}
    };

    if (position == vertical){
        positions[2][0] = {15, 45};
        positions[2][1] = {45, 15};
        positions[3][0] = {15, 45};
        positions[3][2] = {45, 15};
        positions[6][1] = {15, 30};
        positions[6][4] = {45, 30};
    }

    for (int i = 0; i < value && i < 6; ++i) {
        int dotX = x + positions[value][i].x * k;
        int dotY = y + positions[value][i].y * k;
        DrawCircle(dotX, dotY, TILE_HEIGHT / 12 * k, PRUSSIANBLUE);
    }
}
void Tile::draw(float x, float y, Position position, float width, float height) {
    y = WINDOW_HEIGHT - y;
    if (position == horizontal) {
        DrawRectangle(x, y - height, width, height, PAPAYAWHIP);
        DrawRectangleLines(x, y - height, width / 2, height, PRUSSIANBLUE);
        DrawRectangleLines(x + width / 2, y - height, width / 2, height, PRUSSIANBLUE);
        drawDots(x, y - height, left, position, (float)width / TILE_WIDTH);
        drawDots(x + width / 2, y - height, right, position, (float)width / TILE_WIDTH);
    }
    else if (position == vertical){
        DrawRectangle(x, y - width, height, width, PAPAYAWHIP);
        DrawRectangleLines(x, y - width, height, width / 2, PRUSSIANBLUE);
        DrawRectangleLines(x, y - width + width / 2, height, width / 2, PRUSSIANBLUE);
        drawDots(x, y - width, left, position, (float)width / TILE_WIDTH);
        drawDots(x, y - width + width / 2, right, position, (float)width / TILE_WIDTH);
    }
}
void Tile::drawSelected(float x, float y, Position position) {
    y = WINDOW_HEIGHT - y;
    if (position == horizontal) {
        DrawRectangle(x - TILE_HEIGHT / 12, y - TILE_HEIGHT - TILE_HEIGHT / 12, TILE_WIDTH + TILE_HEIGHT / 6, TILE_HEIGHT + TILE_HEIGHT / 6, PRUSSIANBLUE);
        DrawRectangle(x, y - TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, PAPAYAWHIP);
        DrawRectangleLines(x, y - TILE_HEIGHT, TILE_WIDTH / 2, TILE_HEIGHT, PRUSSIANBLUE);
        DrawRectangleLines(x + TILE_WIDTH / 2, y - TILE_HEIGHT, TILE_WIDTH / 2, TILE_HEIGHT, PRUSSIANBLUE);
        drawDots(x, y - TILE_HEIGHT, left, position);
        drawDots(x + TILE_WIDTH / 2, y - TILE_HEIGHT, right, position);
    }
    else if (position == vertical){
        DrawRectangle(x - TILE_HEIGHT / 12, y - TILE_WIDTH - TILE_HEIGHT / 12, TILE_HEIGHT + TILE_HEIGHT / 6, TILE_WIDTH + TILE_HEIGHT / 6, PRUSSIANBLUE);
        DrawRectangle(x, y - TILE_WIDTH, TILE_HEIGHT, TILE_WIDTH, PAPAYAWHIP);
        DrawRectangleLines(x, y - TILE_WIDTH, TILE_HEIGHT, TILE_WIDTH / 2, PRUSSIANBLUE);
        DrawRectangleLines(x, (y - TILE_WIDTH) + TILE_WIDTH / 2, TILE_HEIGHT, TILE_WIDTH / 2, PRUSSIANBLUE);
        drawDots(x, (y - TILE_WIDTH), left, position);
        drawDots(x, (y - TILE_WIDTH) + TILE_WIDTH / 2, right, position);
    }
}