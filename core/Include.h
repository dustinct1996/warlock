#pragma once

#include <SDL.h>
#include "logging/Logging.h"
#include <chrono>
#include <utility>

#include <string>

struct Dimensions {
    int h;
    int w;
};

struct Position {
    float x;
    float y;
};

struct Vector {
    float x;
    float y;
};

struct RenderItem {
    Dimensions size;
    Position position;
    std::string texture;
};