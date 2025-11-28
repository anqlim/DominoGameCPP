#ifndef MENU_H
#define MENU_H
#include "parameters.h"
#include "button.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

class Menu {
private:
    Button play;
    Button records;
public:
    Menu();
    void draw();
    void manage(State& state);
};

#endif
