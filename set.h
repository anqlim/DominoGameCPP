#ifndef SET_H
#define SET_H
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "field.h"

void dealTiles(Player* player, Tile* set, int* count, int num);
void shuffleSet(Tile* set, int count);
void createSet(Tile* set, int* count);
void initGame(Tile* set, User* user, Bot* bot, Field* field, int* count);

#endif
