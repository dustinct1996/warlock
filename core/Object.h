#pragma once

#include <SDL.h>
#include "Engine.h"
#include "Include.h"

class Object {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Object() = default;
    virtual ~Object() = default;
    virtual void update(const unsigned char* keys, float timestep) = 0;
    virtual RenderItem getRenderItem() = 0;
    virtual Position getPosition() = 0;
protected:
    Position position;
    Vector direction;
    Dimensions dimensions;
};