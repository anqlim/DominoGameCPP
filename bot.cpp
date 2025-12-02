#include "bot.h"

namespace {
    void findCandidates(Field &field, Node *head, std::vector<Tile> &candidates) {
        int leftEnd = field.head->tile.left;
        int rightEnd = field.tail->tile.right;
        Node *current = head;
        while (current) {
            if (match(current->tile, leftEnd) || match(current->tile, rightEnd))
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

    void place(Field &field, Node *selected) {
        if (match(selected->tile, field.head->tile.left)) {
            if (field.head->tile.left != selected->tile.right)
                selected->tile.swap();
            field.head->prev = selected;
            selected->next = field.head;
            selected->prev = nullptr;
            field.head = selected;
            return;
        } else if (match(selected->tile, field.tail->tile.right)) {
            if (field.tail->tile.right != selected->tile.left)
                selected->tile.swap();
            field.tail->next = selected;
            selected->prev = field.tail;
            selected->next = nullptr;
            field.tail = selected;
            return;
        }
    }

    bool simulateGameMCTS(std::vector<Tile> set, User& user, Bot& bot, Field& field) {
        PROFILE_SCOPE("simulateGameMCTS()");

        bool botTurn = false;
        const int MAX_MOVES = 10;
        int moves = 0;

        while (moves++ < MAX_MOVES) {
            if (!bot.head) return true;
            if (!user.head) return false;

            Player &currentPlayer = botTurn ? (Player &) bot : (Player &) user;

            if (!currentPlayer.noSolutions(field)) {
                std::vector<Tile> candidates;
                findCandidates(field, currentPlayer.head, candidates);
                Tile selected = candidates[rand() % candidates.size()];

                Node *current = currentPlayer.head;
                while (current && current->tile != selected) current = current->next;
                if (!current) break;

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

    Tile selectMoveMCTS(Bot &bot, Field &field, const std::vector<Tile> &unknown, int userCount) {
        PROFILE_SCOPE("selectMoveMCTS()");

        std::vector<Tile> rootCandidates;
        findCandidates(field, bot.head, rootCandidates);

        std::vector<std::unique_ptr<MCTSNode>> rootChildren;

        for (const auto &candidate: rootCandidates) {
            auto child = std::make_unique<MCTSNode>();

            child->botState.copy(bot);
            child->fieldState.copy(field);

            Node *current = child->botState.head;
            while (current && current->tile != candidate) {
                current = current->next;
            }
            if (!current) continue;

            child->botState.exception(current);
            place(child->fieldState, current);

            child->move = candidate;
            rootChildren.push_back(std::move(child));
        }

        if (rootChildren.empty()) return rootCandidates[0];

        for (int iter = 0; iter < ITERS; ++iter) {
            std::vector<MCTSNode *> path;
            MCTSNode *node = nullptr;
            double bestScore = -1;

            for (auto &child: rootChildren) {
                double score = child->ucb1(ITERS);
                if (score > bestScore) {
                    bestScore = score;
                    node = child.get();
                }
            }
            if (!node) node = rootChildren[0].get();
            path.push_back(node);

            if (node->children.empty()) {
                std::vector<Tile> candidates;
                findCandidates(node->fieldState, node->botState.head, candidates);

                for (const auto &cand: candidates) {
                    auto grandchild = std::make_unique<MCTSNode>();
                    grandchild->botState.copy(node->botState);
                    grandchild->fieldState.copy(node->fieldState);

                    Node *cur = grandchild->botState.head;
                    while (cur && cur->tile != cand) cur = cur->next;
                    if (!cur) continue;

                    grandchild->botState.exception(cur);
                    place(grandchild->fieldState, cur);
                    grandchild->move = cand;

                    node->children.push_back(std::move(grandchild));
                }
            }

            bool simulationResult = false;
            if (!node->children.empty()) {
                auto &simChild = node->children[rand() % node->children.size()];
                std::vector<Tile> simUnknown = unknown;
                shuffleSet(simUnknown);
                User userCopy;
                dealTiles(userCopy, simUnknown, userCount);
                simulationResult = simulateGameMCTS(simUnknown, userCopy, simChild->botState, simChild->fieldState);
                path.push_back(simChild.get());
            }
            else {
                std::vector<Tile> simUnknown = unknown;
                shuffleSet(simUnknown);
                User userCopy;
                dealTiles(userCopy, simUnknown, userCount);
                simulationResult = simulateGameMCTS(simUnknown, userCopy, node->botState, node->fieldState);
            }

            // BACKPROPAGATION
            for (auto *n: path) {
                n->visits++;
                if (simulationResult) n->wins++;
            }
        }

        // Выбор по посещениям
        MCTSNode *best = rootChildren[0].get();
        for (auto &child: rootChildren) {
            if (child->visits > best->visits) {
                best = child.get();
            }
        }

        return best->move;
    }
}

void Bot::move(Field& field, int userCount) {
    PROFILE_SCOPE("bot.move()");

    //Step 1
    std::vector<Tile> candidates;
    findCandidates(field, head, candidates);
    Tile best(candidates[0]);

    if (candidates.size() != 1) {
        //Step 2
        std::vector<Tile> unknown;
        createSet(unknown);
        deleteExisting(field, head, unknown);

        //Step 3
        srand(static_cast<unsigned int>(SEED));
        best = selectMoveMCTS(*this, field, unknown, userCount);
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

double MCTSNode::ucb1(int parentVisits) const {
    if (visits == 0) return INFINITY;
    double exploitation = static_cast<double>(wins) / visits;
    double exploration = sqrt(2.0 * log(parentVisits) / visits);
    return exploitation + exploration;
}

