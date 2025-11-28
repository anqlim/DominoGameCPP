#include "records.h"

Records::Records():exit({1770, 970, 30, 30},
                        FIREBRICK, "x", BARNRED){}
void Records::draw(Result& res) {
    exit.draw();
    switch (res) {
        case WIN:
            DrawText("you won!", 600, WINDOW_HEIGHT - 850, 150, BARNRED);
            break;
        case LOSE:
            DrawText("you lost", 600, WINDOW_HEIGHT - 850, 150, BARNRED);
            break;
        default:
            DrawText("your statistics", 350, WINDOW_HEIGHT - 850, 150, BARNRED);
            break;
    }
    int y_offset = WINDOW_HEIGHT - 650;
    int font_size = 50;

    if (res != DEFAULT) {
    DrawText(("your points: " + std::to_string(statistics.points)).data(), 600, y_offset, font_size, PRUSSIANBLUE);
    y_offset += 70;
    }
    DrawText(("record: " + std::to_string(statistics.record)).data(), 600, y_offset, font_size, PRUSSIANBLUE);
    y_offset += 70;
    DrawText(("games: " + std::to_string(statistics.games)).data(), 600, y_offset, font_size, PRUSSIANBLUE);
    y_offset += 70;
    DrawText(("victories: " + std::to_string(statistics.wins)).data(), 600, y_offset, font_size, PRUSSIANBLUE);
    y_offset += 70;
    DrawText(("percent of victory: " + std::to_string(statistics.winningPercentage) + "%").data(), 600, y_offset, font_size, PRUSSIANBLUE);

}
void Records::manage(State& state, Result& res) {
    draw(res);
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
    Vector2 mouse = GetMousePosition();
    if (exit.isClicked(mouse.x, mouse.y)) {
        state = MENU;
        res = DEFAULT;
    }
}