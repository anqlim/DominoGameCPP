#include <iostream>
#include "raylib/include/raylib.h"
#include "colors.h"
#include "button.h"
#include "tile.h"

int main() {
    InitWindow(1800, 1000, "Domino");
    Button button({100, 100, 200, 100}, FIREBRICK, (std::string)"domino", BARNRED);
    Tile tile(6, 2);

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        button.draw();
        tile.draw(200, 200, vertical);
        tile.draw(400, 400, horizontal);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
