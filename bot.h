#ifndef BOT_H
#define BOT_H
#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
#include "raylib.h"
#include "parameters.h"
#include "player.h"
#include "set.h"
#define ITERS 100

class Bot:public Player {
public:
    void move(Field& field, int userCount);
    void draw();
};

#endif
