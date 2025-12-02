#include "raylib.h"
#include "textures.h"
#include "parameters.h"
#include "game.h"
#include "records.h"
#include "menu.h"
#include "profile.h"

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Domino");
    SetTargetFPS(60);

    State state(MENU);
    Result result(DEFAULT);
    Game game;
    Menu menu;
    Records records;

    generateTextures();

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

    g_profiler.print();
    g_profiler.reset();

    return 0;
}
