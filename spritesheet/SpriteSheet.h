#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Utils.h"

class SpriteSheet {
public:
    SpriteSheet(uint32_t spriteSheetID, const char* pathToTexture, uint16_t spriteSizeX, uint16_t spriteSizeY);
    SpriteSheet(uint32_t spriteSheetID, const char* pathToTexture, uint16_t spriteSizeX, uint16_t spriteSizeY, uint8_t spriteOffset, uint8_t sheetMargin);
    // void requestTexture(uint32_t id, const std::string& path);
    // void releaseTexture(uint32_t id);
    Rectangle getSprite(uint8_t x, uint8_t y) const;
    uint32_t getTextureID() const { return id; };
    const char* getPath() { return filePath; };
    Size getSpriteSize() { return size; };
    uint8_t getOffset() { return offset; };
    uint8_t getMargin() { return margin; };
private:
    uint32_t id;
    Size size;
    uint8_t offset = 0;
    uint8_t margin = 0;
    const char* filePath;
};

#endif // SPRITESHEET_H