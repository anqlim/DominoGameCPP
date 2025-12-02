#ifndef TILE_H
#define TILE_H
#include <unordered_map>
#include "raylib.h"
#include "parameters.h"
#include "profile.h"
#include "textures.h"

constexpr float TILE_WIDTH = 120;
constexpr float TILE_HEIGHT = 60;

enum Position {horizontal, vertical};

class Tile {
public:
    int left;
    int right;
    Tile(int _left, int _right);
    bool operator==(const Tile& other) const;
    void swap();
    void draw(float x, float y, float width = TILE_WIDTH, float height = TILE_HEIGHT);
    void drawTexture(float x, float y, Position position, bool isSelected, float width = TILE_WIDTH, float height = TILE_HEIGHT);
};

#endif
