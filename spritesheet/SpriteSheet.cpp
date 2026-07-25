#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(int spriteSheetID, int spriteSizeX, int spriteSizeY, int spriteOffset, int sheetMargin, std::string pathToTexture):
    id(spriteSheetID), 
    size{spriteSizeX, spriteSizeY},
    offset(spriteOffset),
    margin(sheetMargin),
    filePath(pathToTexture) {}

SDL_Rect SpriteSheet::getSprite(int x, int y) const {
    SDL_Rect sprite;

    sprite.h = size.h;
    sprite.w = size.w;
    sprite.x = margin + (x * size.w) + ((x - 1) * offset);
    sprite.y = margin + (y * size.h) + ((y - 1) * offset);

    return sprite;
}