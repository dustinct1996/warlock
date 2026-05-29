#pragma once

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
    int x;
    int y;
};

struct RenderItem {
    Dimensions size;
    Position position;
    std::string texture;
};