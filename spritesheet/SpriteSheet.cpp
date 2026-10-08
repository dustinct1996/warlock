#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(uint32_t spriteSheetID, const char* pathToTexture, uint16_t spriteSizeX, uint16_t spriteSizeY):
    id(spriteSheetID),
    filePath(pathToTexture),
    size{spriteSizeX, spriteSizeY} {}

SpriteSheet::SpriteSheet(uint32_t spriteSheetID, const char* pathToTexture, uint16_t spriteSizeX, uint16_t spriteSizeY, uint8_t spriteOffset, uint8_t sheetMargin):
    id(spriteSheetID),
    filePath(pathToTexture),
    size{spriteSizeX, spriteSizeY},
    offset(spriteOffset),
    margin(sheetMargin) {}

Rectangle SpriteSheet::getSprite(uint8_t x, uint8_t y/*uint8_t index*/) const {
    Rectangle sprite;

    sprite.h = size.h;
    sprite.w = size.w;
    sprite.x = (x * (size.w + offset)) + margin;
    sprite.y = (y * (size.h + offset)) + margin;

    return sprite;
}