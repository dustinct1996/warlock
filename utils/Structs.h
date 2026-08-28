#ifndef STRUCTS_H
#define STRUCTS_H

#include <optional>
#include <SDL.h>
#include "Enums.h"

struct Size {
    uint32_t h;
    uint32_t w;
};

struct Point {
    float x;
    float y;
};

struct Rectangle {
    int32_t x;
    int32_t y;
    int32_t h;
    int32_t w;
};

struct CollisionBox {
    Rectangle box;

    bool intersects(const Rectangle& otherBox) {
        if(box.x < (otherBox.x + otherBox.w) &&
          (box.x + box.w) > otherBox.x &&
           box.y < (otherBox.y + otherBox.h) &&
          (box.y + box.h) > otherBox.y) {
            return true;
        }

        return false;
    }
};

struct RenderableTexture {
    uint32_t texture;
    Rectangle subTexture;
    Size size;
    Point position;
    double rotation = 0.0;
	std::optional<Point> rotationAxis;
    Reflection reflection = Reflection::NONE;
};

#endif // STRUCTS_H