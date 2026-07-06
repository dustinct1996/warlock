#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Dimensions {
    int h;
    int w;
};

struct Position {
    float x;
    float y;
};

struct Direction {
    float x;
    float y;
};

struct RenderItem {
    Dimensions size;
    Position position;
    std::string texture;
    float ySort;
};

struct BoundingBox {
    Dimensions size;
    Position position;
};

#endif // STRUCTS_H