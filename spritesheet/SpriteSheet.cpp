#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(uint32_t spriteSheetID, uint16_t spriteSizeX, uint16_t spriteSizeY, uint8_t spriteOffset, uint8_t sheetMargin, std::string pathToTexture):
    id(spriteSheetID), 
    size{spriteSizeX, spriteSizeY},
    offset(spriteOffset),
    margin(sheetMargin),
    filePath(pathToTexture) {}

SDL_Rect SpriteSheet::getSprite(uint8_t x, uint8_t y) const {
    SDL_Rect sprite;

    sprite.h = size.h;
    sprite.w = size.w;
    sprite.x = (x * (size.w + offset)) + margin;
    sprite.y = (y * (size.h + offset)) + margin;

    return sprite;
}