#include "menu.h"

Menu::Menu():play({700, 400, 400, 200},
                    FIREBRICK, "play", BARNRED),
                    records({50, 50, 200, 100},
                            FIREBRICK, "records", BARNRED){}
void Menu::draw() {
    play.draw();
    records.draw();
    DrawText("DOMINO", 50, 50, 150, PRUSSIANBLUE);
}
void Menu::manage(State& state) {
    draw();
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
    Vector2 mouse = GetMousePosition();
    srand(static_cast<unsigned int>(SEED));

    if (play.isClicked(mouse.x, mouse.y))
        state = (std::rand() % 2) ? USER_MOVE : BOT_MOVE;
    else if (records.isClicked(mouse.x, mouse.y))
        state = RECORDS;
}