#include <iostream>
#include "raylib.h"
#include "parameters.h"
#include "mouse.h"
#include "button.h"
#include "tile.h"

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Domino");
    Button button({600, 100, 200, 100}, FIREBRICK, (std::string)"domino", BARNRED);
    Tile tile(6, 2);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        mouse.y = WINDOW_HEIGHT - mouse.y;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            manageMouseClick(mouse.x, mouse.y);
        }

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
