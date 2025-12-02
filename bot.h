#ifndef BOT_H
#define BOT_H
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cmath>
#include "raylib.h"
#include "parameters.h"
#include "player.h"
#include "set.h"
#include "profile.h"
constexpr int ITERS = 1000;

class Bot:public Player {
public:
    void move(Field& field, int userCount);
    void draw();
};

struct MCTSNode {
    Tile move;                      // ход, который делает этот узел
    int wins = 0;
    int visits = 0;
    Bot botState;                   // состояние бота ПОСЛЕ хода
    Field fieldState;               // состояние поля ПОСЛЕ хода
    std::vector<std::unique_ptr<MCTSNode>> children;

    MCTSNode(): move(-1, -1) {}

    double ucb1(int parentVisits) const;
};

#endif
