#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "list.h"
#include "field.h"
#include "tile.h"

#define SHIFT 10
#define USER_X 50
#define USER_Y 50
#define BOT_X 50
#define BOT_Y 830

class Player:public List {
public:
    bool noSolutions(Field& field) const;
    void exception(Node* selected);
    int points() const;
    int countTiles() const;
    Player copy();
};

class User:public Player {
public:
    Node* clicked(float mouseX, float mouseY);
    void draw(Node* selected);
};

bool match(Tile& tile, int val);

#endif
