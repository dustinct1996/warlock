#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "Utils.h"

class Entity {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Entity(uint32_t entityId, float x, float y, uint32_t h, uint32_t w) : id(entityId), position{x, y}, dimensions{h, w} {};
    virtual ~Entity() = default;
    virtual void move(const unsigned char* keys, float timestep) = 0;
    virtual RenderableTexture getRenderableTexture() = 0;
    virtual Point getPosition() = 0;
    virtual CollisionBox getCollisionBox() = 0;
    virtual uint32_t getID() = 0;
    virtual bool isSolid() = 0;
protected:
    uint32_t texture;
    Point position;
    Point direction;
    Size dimensions;
    CollisionBox collisionBox;
    uint32_t id;
};

#endif // ENTITY_H