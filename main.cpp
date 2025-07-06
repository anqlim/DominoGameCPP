#include <iostream>
#include "raylib/include/raylib.h"
#include "graphics.h"

int main() {
    InitWindow(800, 600, "Hello Raylib!");

    while (!WindowShouldClose()) {
        ClearBackground(BARNRED);
        BeginDrawing();
        DrawText("Hello Domino!", 100, 100, 100, RAYWHITEgit );
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
