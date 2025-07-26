#ifndef TILE_H
#define TILE_H

#define TILE_WIDTH 120
#define TILE_HEIGHT 60

enum Position {horizontal, vertical};

class Tile {
private:
    int left;
    int right;
public:
    Tile(int _left, int _right);
    void swap();
    void draw(int x, int y, Position position);
};

#endif
