#include "textures.h"

std::unordered_map<int, Texture2D> cache;

int getTileHash(int left, int right, bool isSelected) {
    return left * 100 + right * 10 + (isSelected ? 1 : 0);
}
void generateTextures() {
    for (int left = 0; left <= 6; ++left) {
        for (int right = 0; right <= 6; ++right) {
            Tile temp(left, right);
            RenderTexture2D target = LoadRenderTexture(TILE_HEIGHT + 1, TILE_WIDTH + 1);
            BeginTextureMode(target);
            {
                ClearBackground(RAYWHITE);
                temp.draw(1, TILE_WIDTH);
            }
            EndTextureMode();
            int hash = getTileHash(left, right, false);
            cache[hash] = target.texture;

            RenderTexture2D targetSel = LoadRenderTexture(TILE_HEIGHT + TILE_HEIGHT / 6, TILE_WIDTH + TILE_HEIGHT / 6);
            BeginTextureMode(targetSel);
            {
                ClearBackground(PRUSSIANBLUE);
                temp.draw(1 + TILE_HEIGHT / 12, TILE_WIDTH + TILE_HEIGHT / 12);
            }
            EndTextureMode();
            hash = getTileHash(left, right, true);
            cache[hash] = targetSel.texture;
        }
    }
}