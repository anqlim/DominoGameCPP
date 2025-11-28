#include "raylib.h"
#include "parameters.h"
#include "game.h"
#include "records.h"
#include "menu.h"

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
            default: game.manage(state, result, records.statistics); break;
        }
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
