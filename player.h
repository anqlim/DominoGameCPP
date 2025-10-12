#ifndef PLAYER_H
#define PLAYER_H
#include "list.h"

class Player {
public:
    Player();
    ~Player();
    Node* head;
    Node* tail;
};

class Bot:public Player {
public:
    int move();
    void draw();
};

class User:public Player {
public:
    void draw();
};

#endif
