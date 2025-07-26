#ifndef PLAYER_H
#define PLAYER_H
#include "list.h"

class Player {
public:
    Node* prev;
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
