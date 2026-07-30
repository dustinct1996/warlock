#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Utils.h"

class SpriteSheet {
public:
    SpriteSheet(unsigned int spriteSheetID, int spriteSizeX, int spriteSizeY, unsigned char spriteOffset, unsigned char sheetMargin, std::string pathToTexture);
    SDL_Rect getSprite(int x, int y) const;
    unsigned int getTextureID() const { return id; };
    std::string getPath() { return filePath; };
private:
    unsigned int id;
    Size size;
    unsigned char offset;
    unsigned char margin;
    std::string filePath;
};

#endif // SPRITESHEET_H