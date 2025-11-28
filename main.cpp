#include "raylib.h"
#include "parameters.h"
#include "game.h"
#include "records.h"
#include "menu.h"

double manageTime = 0.0;

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Domino");

    State state(MENU);
    Result result(DEFAULT);
    Game game;
    Menu menu;
    Records records;

    while (!WindowShouldClose()) {
        ClearBackground(GRAYISHBLUE);
        BeginDrawing();
        switch (state) {
            case MENU: menu.manage(state); break;
            case RECORDS: records.manage(state, result); break;
            default: {
                double start = GetTime(), end;
                game.manage(state, result, records.statistics);
                end = GetTime();
                manageTime = ((end - start) > manageTime) ? (end - start) : manageTime;
                break;
            }
        }
        EndDrawing();

    }
    CloseWindow();

    std::cout << "simulateGame(): " << simulateGameTime * 1000 << " ms" << std::endl;
    std::cout << "move(): " << moveTime * 1000 << " ms" << std::endl;
    std::cout << "game.manage(): " << manageTime * 1000 << " ms" << std::endl;

    return 0;
}
