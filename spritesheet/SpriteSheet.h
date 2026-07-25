#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Utils.h"

class SpriteSheet {
public:
    SpriteSheet(int spriteSheetID, int spriteSizeX, int spriteSizeY, int spriteOffset, int sheetMargin, std::string pathToTexture);
    SDL_Rect getSprite(int x, int y) const;
    int getTextureID() const { return id; };
    std::string getPath() { return filePath; };
private:
    int id;
    Size size;
    char offset;
    char margin;
    std::string filePath;
};

#endif // SPRITESHEET_H