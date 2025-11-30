#ifndef BOT_H
#define BOT_H
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
#include "raylib.h"
#include "parameters.h"
#include "player.h"
#include "set.h"
#include "profile.h"
#define ITERS 1000

class Bot:public Player {
public:
    void move(Field& field, int userCount);
    void draw();
};

#endif
