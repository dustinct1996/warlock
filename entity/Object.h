#pragma once

#include <SDL.h>
#include "Engine.h"
#include "RenderItem.h"

class Object {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Object() = default;
    virtual ~Object() = default;
    virtual void init (int x, int y, int h, int w) = 0;
    virtual void update(const unsigned char* keys) = 0;
    virtual RenderItem getRenderItem() = 0;
protected:
    Position position;
    Dimensions dimensions;
};