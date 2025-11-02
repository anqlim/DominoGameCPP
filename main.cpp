#include "raylib.h"
#include "parameters.h"
#include "game.h"
#include "records.h"
#include "menu.h"
#include "button.h"
#include "tile.h"

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Domino");
    Button button({600, 100, 200, 100}, FIREBRICK, "domino", BARNRED);
    Tile tile(6, 2);

    State state(MENU);
    Result result(DEFAULT);
    Game game;
    Menu menu;
    Records records;

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        BeginDrawing();

        switch (state) {
            case MENU: menu.manage(state); break;
            case RECORDS: records.manage(state, result); break;
            default: game.manage(state, result); break;
        }

        button.draw();
        tile.draw(200, 200, vertical);
        tile.draw(400, 400, horizontal);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
