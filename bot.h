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

struct MCTSNode {
    Tile move;                      // ход, который делает этот узел
    int wins = 0;
    int visits = 0;
    Bot botState;                   // состояние бота ПОСЛЕ хода
    Field fieldState;               // состояние поля ПОСЛЕ хода
    std::vector<std::unique_ptr<MCTSNode>> children;

    // UCB1 формула: баланс эксплуатации и исследования
    double ucb1(int parentVisits) const {
        if (visits == 0) return INFINITY;
        double exploitation = static_cast<double>(wins) / visits;
        double exploration = sqrt(2.0 * log(parentVisits) / visits);
        return exploitation + exploration;
    }
};

#endif
