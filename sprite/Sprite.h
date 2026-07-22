#include <SDL.h>
#include "Structs.h"

class Sprite {
public:
    Sprite(int spriteSheetID, int indexX, int indexY, int sizeX, int sizeY);
    int getSpriteSheetID();
    SDL_Rect getSprite();    
private:
    int ID; // sprite sheet ID
    int spriteIndexX;
    int spriteIndexY;
    Size spriteDimensions; // size of each sprite on sprite sheet
};