#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "Utils.h"

class Entity {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Entity() = default;
    virtual ~Entity() = default;
    virtual void update(const unsigned char* keys, float timestep) = 0;
    virtual RenderItem getRenderItem() = 0;
    virtual Position getPosition() = 0;
    // virtual BoundingBox getBoundingBox() = 0;
    virtual std::string getName() = 0;
protected:
    Position position;
    Direction direction;
    Dimensions dimensions;
    // BoundingBox boundingBox;
};

#endif // ENTITY_H