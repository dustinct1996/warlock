#ifndef TILEDMAP_H
#define TILEDMAP_H

#include "tileson.hpp"
#include "Utils.h"
#include "SpriteSheet.h"
#include "AnimatedSprite.h"
#include "AnimationState.h"
#include "LayerStack.h"

struct Transformations {
    double rotation;
	Reflection reflection;
};

struct AnimatedTile {
    AnimatedSprite sprite;
    AnimationState state;
    RenderableTexture* renderableTexture = nullptr;

    AnimatedTile(std::vector<InputFrame> newFrames, float frameIncrementationTrigger = 0.1) : 
        sprite(newFrames), state(frameIncrementationTrigger) {};
};

class TiledMap {
public:
    TiledMap(std::vector<SpriteSheet*> spriteSheets, const std::string& mapPath);
    std::vector<RenderableTexture> getBackgroundTiles();
    std::vector<RenderableTexture> getForegroundTiles();
    std::vector<RenderableTexture> getEntities();
    tson::Colori getBackgroundColor();
    void update(float timestep);
private:
    tson::Colori backgroundColor;
    std::vector<Rectangle> collisionObjects;
    Point bounds[4] = {
        {231, 231},
        {231, 570},
        {570, 570},
        {570, 231}
    };
    LayerStack<RenderableTexture> tileLayers;
    std::vector<RenderableTexture> backgroundTiles;
    std::vector<RenderableTexture> foregroundTiles;
    std::vector<RenderableTexture> entities;
    std::vector<SpriteSheet*> spriteSheets;
    std::vector<AnimatedTile> animatedTiles;
    Size tileSize = {16, 16};
    Transformations convertedTransformations[8] = {
        {
            0.0,
            Reflection::NONE
        },
        {
            0.0,
            Reflection::HORIZONTAL
        },
        {
            0.0,
            Reflection::VERTICAL
        },
        {
            180.0,
            Reflection::NONE
        },
        {
            90.0,
            Reflection::VERTICAL
        },
        {
            90.0,
            Reflection::NONE
        },
        {
            270.0,
            Reflection::NONE
        },
        {
            90.0,
            Reflection::HORIZONTAL
        }
    };
};

#endif // TILEDMAP_H