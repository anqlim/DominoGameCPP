#ifndef TEXTURES_H
#define TEXTURES_H
#include "raylib.h"
#include "profile.h"
#include "tile.h"
#include "button.h"

extern std::unordered_map<int, Texture2D> cache;

int getTileHash(int left, int right, bool isSelected = false);
void generateTextures();

#endif
