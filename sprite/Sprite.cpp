#include "Sprite.h"

Sprite::Sprite(
    int spriteSheetID,
    int indexX,
    int indexY,
    int sizeH,
    int sizeW): 
    ID(spriteSheetID),
    spriteIndexX(indexX),
    spriteIndexY(indexY),
    spriteDimensions{sizeH, sizeW} {}

int Sprite::getSpriteSheetID() {
    return ID;
}

SDL_Rect Sprite::getSprite() {
    SDL_Rect srcRect;

    srcRect.w = spriteDimensions.w;
    srcRect.h = spriteDimensions.h;
    srcRect.x = spriteIndexX * spriteDimensions.w;
    srcRect.y = spriteIndexY * spriteDimensions.h;

    return srcRect;
}