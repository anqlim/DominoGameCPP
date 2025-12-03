#include "bot.h"

namespace {
    void findCandidates(Field &field, Node *head, std::vector<Tile> &candidates) {
        Node *current = head;
        while (current) {
            if (match(current->tile, field.head->tile.left) || match(current->tile, field.tail->tile.right))
                candidates.push_back(current->tile);
            current = current->next;
        }
    }

    void deleteExisting(Field &field, Node *head, std::vector<Tile> &unknown) {
        Node *current = head;
        while (current) {
            auto i = std::find(unknown.begin(), unknown.end(), current->tile);
            if (i != unknown.end()) unknown.erase(i);
            current = current->next;
        }

        current = field.head;
        while (current) {
            auto i = std::find(unknown.begin(), unknown.end(), current->tile);
            if (i != unknown.end()) unknown.erase(i);
            current = current->next;
        }
    }

    void place(Field &field, Node* selected) {
        if (match(selected->tile, field.head->tile.left)) {
            if (field.head->tile.left != selected->tile.right)
                selected->tile.swap();
            field.head->prev = selected;
            selected->next = field.head;
            selected->prev = nullptr;
            field.head = selected;
            return;
        }
        else if (match(selected->tile, field.tail->tile.right)) {
            if (field.tail->tile.right != selected->tile.left)
                selected->tile.swap();
            field.tail->next = selected;
            selected->prev = field.tail;
            selected->next = nullptr;
            field.tail = selected;
            return;
        }
    }

    bool simulateGame(std::vector<Tile> set, User& user, Bot& bot, Field& field) {
        PROFILE_SCOPE("simulateGame()");
        bool botTurn = false;

        while (true) {
            if (!bot.head) return true;
            if (!user.head) return false;


            Player &currentPlayer = botTurn ? (Player &) bot : (Player &) user;

            if (!currentPlayer.noSolutions(field)) {
                std::vector<Tile> candidates;
                findCandidates(field, currentPlayer.head, candidates);
                Tile selected = candidates[rand() % (candidates.size())];

                Node *current = currentPlayer.head;
                while (current) {
                    if (current->tile == selected) break;
                    current = current->next;
                }
                currentPlayer.exception(current);
                place(field, current);

                botTurn = !botTurn;
                continue;
            }

            if (!set.empty()) {
                dealTiles(currentPlayer, set, 1);
                if (currentPlayer.noSolutions(field)) botTurn = !botTurn;
            }
            else {
                Player &enemy = botTurn ? (Player &) user : (Player &) bot;
                if (!enemy.noSolutions(field)) botTurn = !botTurn;
                else break;
            }
        }
        return user.countTiles() > bot.countTiles() ||
               (user.countTiles() == bot.countTiles() && user.points() > bot.points());
    }
}

void Bot::move(Field& field, int userCount) {
    PROFILE_SCOPE("bot.move()");

    //Step 1
    std::vector<Tile> candidates;
    findCandidates(field, head, candidates);

    //Step 2
    std::vector<Tile> unknown;
    createSet(unknown);
    deleteExisting(field, head, unknown);

    //Step 3
    srand(static_cast<unsigned int>(SEED));
    int mx(-1);
    Tile best(candidates[0]);

    for (auto& candidate : candidates) {
        int wins = 0;

        for (int i(0); i < ITERS; i++) {
            std::vector<Tile> unknownCopy = unknown;
            shuffleSet(unknownCopy);
            Bot botCopy = static_cast<Bot>(this->copy());
            Field fieldCopy = field.copy();

            Node *current = botCopy.head;
            while (current) {
                if (current->tile == candidate) break;
                current = current->next;
            }
            botCopy.exception(current);
            place(fieldCopy, current);

            User userCopy;
            dealTiles(userCopy, unknownCopy, userCount);

            if (simulateGame(unknownCopy, userCopy, botCopy, fieldCopy)) {
                wins++;
            }
        }
        if (wins > mx) {
            mx = wins;
            best = candidate;
        }
    }

    //Step 4
    Node* current = head;
    while (current) {
        if (current->tile == best) break;
        current = current->next;
    }
    exception(current);
    place(field, current);
}

void Bot::draw() {
    Node* current = head;
    int x = BOT_X;
    while (current) {
        DrawRectangle(x, WINDOW_HEIGHT - BOT_Y - TILE_WIDTH, TILE_HEIGHT, TILE_WIDTH, AIRSUPERIORITYBLUE);
        DrawRectangleLines(x, WINDOW_HEIGHT - BOT_Y - TILE_WIDTH, TILE_HEIGHT, TILE_WIDTH, PRUSSIANBLUE);
        x += TILE_HEIGHT + SHIFT;
        current = current->next;
    }
}
