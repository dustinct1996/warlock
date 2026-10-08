#ifndef TILELAYER_H
#define TILELAYER_H

#include <SDL.h>
#include "Entity.h"
#include "Utils.h"

class TileLayer : public Entity {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    TileLayer(uint32_t entityId, std::vector<RenderableTexture> tileLayer) : Entity(entityId), tiles(std::move(tileLayer)) {};
    virtual ~TileLayer() = default;
    virtual RenderableTexture getRenderableTextures() = 0;
protected:
    std::vector<RenderableTexture> tiles;
};

#endif // TILELAYER_H