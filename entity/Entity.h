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
    virtual WorldEntity getWorldEntity() = 0;
    virtual Point getPosition() = 0;
    // virtual SDL_Rect getBoundingBox() = 0;
    virtual std::string getName() = 0;
    virtual bool isSolid() = 0;
protected:
    Point position;
    Point direction;
    Size dimensions;
    SDL_Rect boundingBox;
};

#endif // ENTITY_H