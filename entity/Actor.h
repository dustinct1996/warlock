#ifndef ACTOR_H
#define ACTOR_H

#include <SDL.h>
#include "Entity.h"
#include "Graphic.h"
#include "Utils.h"

class Actor : public Entity {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Actor(uint32_t entityId, float x, float y) : Entity(entityId, x, y) {};
    virtual ~Actor() = default;
    virtual RenderableTexture getRenderableTexture() = 0;
    virtual Point getPosition() = 0;
    virtual Graphic& getGraphic() = 0;
    // virtual CollisionBox getCollisionBox() = 0;
protected:
    Point direction;
    // CollisionBox collisionBox;
};

#endif // ACTOR_H