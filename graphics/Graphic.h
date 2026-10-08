#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Utils.h"

class Renderer;
class AssetManager;

class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void render(Renderer& renderer, Point position, float zoom, AssetManager* assetManager = nullptr) = 0;
};

#endif // GRAPHIC_H