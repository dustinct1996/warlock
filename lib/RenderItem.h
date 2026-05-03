#pragma once

#include <string>

struct Dimensions {
    int h;
    int w;
};

struct Position {
    int x;
    int y;
};

struct RenderItem {
    Dimensions size;
    Position position;
    std::string texture;
};