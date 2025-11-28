#ifndef SET_H
#define SET_H
#include <cstdlib>
#include <ctime>
#include <vector>
#include "player.h"
#include "field.h"

class Bot;

void dealTiles(List& list, std::vector<Tile>& set, int num);
void shuffleSet(std::vector<Tile>& set);
void createSet(std::vector<Tile>& set);
void initSet(std::vector<Tile>& set, User& user, Bot& bot, Field& field);

#endif
