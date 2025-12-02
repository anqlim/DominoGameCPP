#ifndef TEXTURES_H
#define TEXTURES_H
#include "raylib.h"
#include "profile.h"
#include "tile.h"
#include "button.h"

extern std::unordered_map<int, Texture2D> cache;

inline int getTileHash(int left, int right, bool isSelected = false) {
    return left * 100 + right * 10 + (isSelected ? 1 : 0);
}
void generateTextures();

#endif
