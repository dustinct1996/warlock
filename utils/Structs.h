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

#endif // STRUCTS_H