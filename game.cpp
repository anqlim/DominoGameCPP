#include "game.h"

Game::Game():bazaar({1570, 30, 200, 200},
                    FIREBRICK, "bazaar", BARNRED),
                    exit({1770, 970, 30, 30},
                         FIREBRICK, "x", BARNRED){
    initSet(set, user, bot, field);
}
void Game::draw() {
    PROFILE_SCOPE("game.draw()");
    user.draw(selected);
    bot.draw();
    field.draw();
    bazaar.draw();
    DrawText(std::to_string(set.size()).data(), 1655, WINDOW_HEIGHT - 100, 50, BARNRED);
    exit.draw();
}
void Game::manage(State& state, Result& res, Statistics& statistics) {
    PROFILE_SCOPE("game.manage()");
    draw();

    if (state == BOT_MOVE) {
        if (bot.noSolutions(field)) {
            if (set.empty() && user.noSolutions(field)) {
                res = (user.countTiles() > bot.countTiles() || (user.countTiles() == bot.countTiles() && user.points() > bot.points())) ? LOSE : WIN;
                state = RECORDS;
                end(res, statistics);
                return;
            }

            dealTiles(bot, set, 1);
            if (bot.noSolutions(field)) {
                state = USER_MOVE;
                return;
            }
        }
        bot.move(field, user.countTiles());
        if (bot.head == nullptr) {
            res = LOSE;
            state = RECORDS;
            end(res, statistics);
            return;
        }
        state = USER_MOVE;
    }
    else if (state == USER_MOVE) {
        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
        Vector2 mouse = GetMousePosition();

        if (bazaar.isClicked(mouse.x, mouse.y) && user.noSolutions(field)) {
            selected = nullptr;
            if (set.empty() && bot.noSolutions(field)) {
                res = (user.countTiles() > bot.countTiles() || (user.countTiles() == bot.countTiles() && user.points() > bot.points())) ? LOSE : WIN;
                state = RECORDS;
                end(res, statistics);
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
        else if (user.clicked(mouse.x, WINDOW_HEIGHT - mouse.y)){
            selected = user.clicked(mouse.x, WINDOW_HEIGHT - mouse.y);
        }
        else if (selected){
            if (match(selected->tile, field.head->tile.left)
                && mouse.x < WINDOW_WIDTH / 2) {
                user.exception(selected);
                if (field.head->tile.left != selected->tile.right)
                    selected->tile.swap();
                field.head->prev = selected;
                selected->next = field.head;
                selected->prev = nullptr;
                field.head = selected;
                selected = nullptr;
                state = BOT_MOVE;
            }
            else if (match(selected->tile, field.tail->tile.right)
                     && mouse.x > WINDOW_WIDTH / 2) {
                user.exception(selected);
                if (field.tail->tile.right != selected->tile.left)
                    selected->tile.swap();
                field.tail->next = selected;
                selected->prev = field.tail;
                selected->next = nullptr;
                field.tail = selected;
                selected = nullptr;
                state = BOT_MOVE;
            }
            if (user.head == nullptr) {
                res = WIN;
                state = RECORDS;
                end(res, statistics);
                return;
            }
        }
    }
}

void Game::reset() {
    user = User();
    bot = Bot();
    field = Field();
    set.clear();
    initSet(set, user, bot, field);
}

void Game::end (Result& res, Statistics& statistics) {
    statistics.games++;
    if (res == WIN) statistics.wins++;
    statistics.recalculatePercentage();
    statistics.points = bot.points();
    if (statistics.points > statistics.record)
        statistics.record = statistics.points;
    statistics.save();
    reset();
}

