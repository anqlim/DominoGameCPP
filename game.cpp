#include "game.h"

Game::Game():bazaar(Rectangle{1500, 100, 200, 200},
                    FIREBRICK, "bazaar", BARNRED),
                    exit(Rectangle{1770, 970, 30, 30},
                         FIREBRICK, "x", BARNRED){
    initSet(set, user, bot, field);
}
void Game::draw() {
    user.draw();
    bot.draw();
    field.draw();
    bazaar.draw();
    exit.draw();
}
void Game::manage(State& state, Result& res) {
    this->draw();

    if (state == BOT_MOVE) {
        delay(1);
        bot.move();
        if (bot.head == nullptr) {
            delay(1);
            state = RECORDS;
            res = LOSE;
            return;
        }
        state = USER_MOVE;
    }

    else if (state == USER_MOVE) {
        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
        Vector2 mouse = GetMousePosition();
        mouse.y = WINDOW_HEIGHT - mouse.y;

        if (bazaar.isClicked(mouse.x, mouse.y) && user.noSolutions(field)) {
            if (set.empty() && bot.noSolutions(field)) {
                delay(1);
                state = RECORDS;
                res = (user.points() > bot.points()) ? LOSE : WIN;
                return;
            }

            dealTiles(user, set, 1);
            if (!match(user.head->tile, field.head->tile.left) && !match(user.head->tile, field.tail->tile.right)) {
                state = BOT_MOVE;
                return;
            }
        }
        else if (exit.isClicked(mouse.x, mouse.y)) {
            state = MENU;
            return;
        }
        else {
            static Node* selected = nullptr;
            if (!selected) //выбор костяшки
                selected = user.clicked(mouse.x, mouse.y);

            else { //вставка в поле
                if (match(selected->tile, field.head->tile.left)
                && mouse.x < WINDOW_WIDTH / 2 ) {
                    user.exception(selected);
                    if (field.head->tile.left != selected->tile.right)
                        selected->tile.swap();
                    field.head->prev = selected;
                    selected->next = field.head;
                    selected->prev = nullptr;
                    field.head = selected;
                }
                else if (match(selected->tile, field.tail->tile.right)
                    && mouse.x > WINDOW_WIDTH / 2 ) {
                    user.exception(selected);
                    if (field.tail->tile.right != selected->tile.left)
                        selected->tile.swap();
                    field.tail->next = selected;
                    selected->prev = field.tail;
                    selected->next = nullptr;
                    field.tail = selected;
                }

                if (user.head == nullptr) {
                    delay(1);
                    state = RECORDS;
                    res = WIN;
                    return;
                }
            }
        }
    }
}

void delay(double seconds) {
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

