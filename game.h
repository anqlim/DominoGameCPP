#ifndef GAME_H
#define GAME_H
#include <vector>
#include <thread>
#include <chrono>
#include "raylib.h"
#include "parameters.h"
#include "player.h"
#include "field.h"
#include "button.h"
#include "set.h"

void delay(double seconds);

class Game {
private:
    User user;
    Bot bot;
    Field field;
    std::vector<Tile> set;
    Button bazaar;
    Button exit;
public:
    Game();
    void draw();
    void manage(State& state, Result& res);
    void end();
};

#endif
