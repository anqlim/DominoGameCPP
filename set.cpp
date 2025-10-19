#include "set.h"

void initGame(Tile* set, User* user, Bot* bot, Field* field, int* count) {
    createSet(set, count);
    shuffleSet(set, *count);
    dealTiles(user, set, count, 7);
    dealTiles(bot, set, count, 7);
    dealTiles((Player*) field, set, count, 1);
}
void createSet(Tile* set, int* count) {
    *count = 0;
    for (int a = 0; a <= 6; a++)
        for (int b = a; b <= 6; b++) set[(*count)++] = {a, b};
}
void shuffleSet(Tile* set, int count) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Tile temp = set[i];
        set[i] = set[j];
        set[j] = temp;
    }
}
void dealTiles(Player* player, Tile* set, int* count, int num) {
    for (int i = 0; i < num && *count > 0; i++)
        player->head->add(set[--(*count)]);
}