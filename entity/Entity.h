#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "Utils.h"

// class Renderer

class Entity {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Entity(uint32_t entityId, float x, float y) : id(entityId), position{x, y} {};
    virtual ~Entity() = default;
    // virtual void render();
    virtual void move(const unsigned char* keys, float timestep) = 0;
    virtual uint32_t getID() = 0;
protected:
    uint32_t id;
    uint32_t depth;
    Point position;
};

#endif // ENTITY_H

/*
WorldEntity (Player, enemies, etc.)
Items (chests, sword, etc.)
TileLayer
*/