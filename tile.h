#ifndef TILE_H
#define TILE_H

#define TILE_WIDTH (float)120
#define TILE_HEIGHT (float)60

enum Position {horizontal, vertical};

class Tile {
public:
    int left;
    int right;
    Tile(int _left, int _right);
    bool operator==(const Tile& other) const;
    void swap();
    void draw(float x, float y, Position position, float width = TILE_WIDTH, float height = TILE_HEIGHT);
    void drawSelected(float x, float y, Position position);
};

#endif
