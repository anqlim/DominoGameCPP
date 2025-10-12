#include "tile.h"
#include "raylib.h"
#include "parameters.h"

Tile::Tile(int _left, int _right) : left(_left), right(_right) {}

void Tile::swap() {
    int temp = left;
    left = right;
    right = temp;
}

void drawDots(int x, int y, int value, Position position) {
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
        int dotX = x + positions[value][i].x;
        int dotY = y + positions[value][i].y;
        DrawCircle(dotX, dotY, TILE_HEIGHT / 12, PRUSSIANBLUE);
    }
}

void Tile::draw(int x, int y, Position position) {
    y = WINDOW_HEIGHT - y;
    if (position == horizontal) {
        DrawRectangle(x, y, TILE_WIDTH, TILE_HEIGHT, PAPAYAWHIP);
        DrawRectangleLines(x, y, TILE_WIDTH / 2, TILE_HEIGHT, PRUSSIANBLUE);
        DrawRectangleLines(x + TILE_WIDTH / 2, y, TILE_WIDTH / 2, TILE_HEIGHT, PRUSSIANBLUE);
        drawDots(x, y, left, position);
        drawDots(x + TILE_WIDTH / 2, y, right, position);
    }
    else if (position == vertical){
        DrawRectangle(x, y, TILE_HEIGHT, TILE_WIDTH, PAPAYAWHIP);
        DrawRectangleLines(x, y, TILE_HEIGHT, TILE_WIDTH / 2, PRUSSIANBLUE);
        DrawRectangleLines(x, y + TILE_WIDTH / 2, TILE_HEIGHT, TILE_WIDTH / 2, PRUSSIANBLUE);
        drawDots(x, y, left, position);
        drawDots(x, y + TILE_WIDTH / 2, right, position);
    }
}