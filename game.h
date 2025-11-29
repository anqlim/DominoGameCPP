#ifndef GAME_H
#define GAME_H
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include "raylib.h"
#include "parameters.h"
#include "player.h"
#include "bot.h"
#include "field.h"
#include "button.h"
#include "set.h"
#include "statistics.h"

extern double manageTime;

class Game {
private:
    User user;
    Node* selected;
    Bot bot;
    Field field;
    std::vector<Tile> set;
    Button bazaar;
    Button exit;
public:
    Game();
    void draw();
    void manage(State& state, Result& res, Statistics& statistics);
    void reset();
    void end(Result& res, Statistics& statistics);
};

#endif
