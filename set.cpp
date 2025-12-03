#include "set.h"
#include "bot.h"

void initSet(std::vector<Tile>& set, User& user, Bot& bot, Field& field) {
    createSet(set);
    shuffleSet(set);
    dealTiles(user, set, 7);
    dealTiles(bot, set, 7);
    dealTiles((Player&) field, set, 1);
}
void createSet(std::vector<Tile>& set) {
    for (int a = 0; a <= 6; a++)
        for (int b = a; b <= 6; b++) set.push_back(Tile(a, b));
}
void shuffleSet(std::vector<Tile>& set) {
    srand(static_cast<unsigned int>(SEED));
    for (int i = set.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Tile temp = set[i];
        set[i] = set[j];
        set[j] = temp;
    }
}
void dealTiles(List& list, std::vector<Tile>& set, int num) {
    for (int i = 0; i < num && set.size() > 0; i++) {
        if (list.head) {
            list.head->add(set.back());
            list.head = list.head->prev;
        }
        else {
            Node* newNode = new Node(set.back());
            list.head = newNode;
            list.tail = newNode;
        }
        set.pop_back();
    }
}