#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>
#include <string>

struct Size {
    uint32_t h;
    uint32_t w;
};

struct Point {
    float x;
    float y;
};

struct CollisionBox {
    SDL_Rect box;

    bool intersects(const SDL_Rect& otherBox) {
        if(box.x < (otherBox.x + otherBox.w) &&
          (box.x + box.w) > otherBox.x &&
           box.y < (otherBox.y + otherBox.h) &&
          (box.y + box.h) > otherBox.y) {
            return true;
        }

        return false;
    }
};

struct WorldEntity {
    SDL_Rect spriteSheetLocation;
    Size size;
    Point worldPosition;
    uint32_t texture;
};

#endif // STRUCTS_H