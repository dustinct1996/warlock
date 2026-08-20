#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Utils.h"

class SpriteSheet {
public:
    SpriteSheet(uint32_t spriteSheetID, uint16_t spriteSizeX, uint16_t spriteSizeY, uint8_t spriteOffset, uint8_t sheetMargin, std::string pathToTexture);
    SDL_Rect getSprite(uint8_t x, uint8_t y) const;
    uint32_t getTextureID() const { return id; };
    std::string getPath() { return filePath; };
    Size getSpriteSize() { return size; };
    uint8_t getOffset() { return offset; };
    uint8_t getMargin() { return margin; };
private:
    uint32_t id;
    Size size;
    uint8_t offset = 0;
    uint8_t margin = 0;
    std::string filePath;
};

#endif // SPRITESHEET_H