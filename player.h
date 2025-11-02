#ifndef PLAYER_H
#define PLAYER_H
#include "list.h"
#include "field.h"
#include "tile.h"

#define SHIFT 10
#define USER_X 50
#define USER_Y 50
#define BOT_X 50
#define BOT_Y 800

bool match(Tile& tile, int val);

class Player {
public:
    Node* head;
    Node* tail;
    Player();
    ~Player();
    bool noSolutions(Field& field);
    void exception(Node* selected);
    int points();
};

class Bot:public Player {
public:
    void move();
    void draw();
};

class User:public Player {
public:
    Node* clicked(float mouseX, float mouseY);
    void draw();
};

#endif
