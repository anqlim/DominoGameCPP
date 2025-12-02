#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "profile.h"
#include "list.h"
#include "field.h"
#include "tile.h"

constexpr int SHIFT = 10;
constexpr int USER_X = 50;
constexpr int USER_Y = 50;
constexpr int BOT_X = 50;
constexpr int BOT_Y = 830;

class Player:public List {
public:
    bool noSolutions(Field& field) const;
    void exception(Node* selected);
    int points() const;
    int countTiles() const;
    void copy(Player& other);
};

class User:public Player {
public:
    Node* clicked(float mouseX, float mouseY);
    void draw(Node* selected);
};

inline bool match(Tile& tile, int val) {
    return tile.left == val || tile.right == val;
}

#endif
