#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>
#include <string>

struct Size {
    int h;
    int w;
};

struct Point {
    float x;
    float y;
};

struct WorldEntity {
    SDL_Rect spriteSheetLocation;
    Size size;
    Point worldPosition;
    int texture;
};

struct CollisionBox {
    Size box;

    bool intersects(const Size& otherBox) {
        if(box.x < (otherBox.x + otherBox.w) &&
          (box.x + box.w) > otherBox.x &&
           box.y < (otherBox.y + otherBox.h) &&
          (box.y + box.h) > otherBox.y) {
            return true;
        }

        return false;
    }
};

#endif // STRUCTS_H