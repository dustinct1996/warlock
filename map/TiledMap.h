#ifndef TILEDMAP_H
#define TILEDMAP_H

#include "tileson.hpp"
#include "Logging.h"
#include "Utils.h"
#include "SpriteSheet.h"
#include "AnimatedSprite.h"
#include "AnimationState.h"

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
    TiledMap(std::vector<SpriteSheet*> spriteSheets) {
        this->spriteSheets = spriteSheets;

        tson::Tileson t;
        std::unique_ptr<tson::Map> map = t.parse("assets/maps/DevMap.tmj");
        backgroundColor = map->getBackgroundColor();

        for (auto& layer : map->getLayers()) {
            for(auto &[pos, tileObject] : layer.getTileObjects()) {
                std::string layerType = 
                    std::any_cast<std::string>(layer.getProperties().getProperty("layer")->getValue());

                RenderableTexture tile;
                tile.position.x = tileObject.getPosition().x;
                tile.position.y = tileObject.getPosition().y;
                tile.size.w = tileObject.getTile()->getTileSize().x;
                tile.size.h = tileObject.getTile()->getTileSize().y;

                tson::Tileset* spriteSheet = tileObject.getTile()->getTileset();
                tson::Rect subTexture = tileObject.getDrawingRect();
                
                for(int i = 0; i < spriteSheets.size(); i++) {
                    if(spriteSheets[i]->getPath().substr(6) == spriteSheet->getImage().u8string().substr(2)) {
                        tile.texture = spriteSheets[i]->getTextureID();

                        uint8_t offset = spriteSheets[i]->getOffset();
                        uint8_t margin = spriteSheets[i]->getMargin();

                        tile.subTexture.x = subTexture.x;
                        tile.subTexture.y = subTexture.y;
                        tile.subTexture.w = subTexture.width;
                        tile.subTexture.h = subTexture.height;
                    }
                }

                uint8_t flipBits = 0;
                auto flipFlags = tileObject.getTile()->getFlipFlags();

                if((flipFlags & tson::TileFlipFlags::Horizontally) == tson::TileFlipFlags::Horizontally){
                    flipBits |= 1;
                }
                if((flipFlags & tson::TileFlipFlags::Vertically) == tson::TileFlipFlags::Vertically){
                    flipBits |= 2;
                }
                if((flipFlags & tson::TileFlipFlags::Diagonally) == tson::TileFlipFlags::Diagonally) {
                    flipBits |= 4;
                }

                tile.rotation = convertedTransformations[flipBits].rotation;
                tile.reflection = convertedTransformations[flipBits].reflection;

                if(layerType == "background") {
                    backgroundTiles.emplace_back(tile);
                } else if(layerType == "foreground") {
                    foregroundTiles.emplace_back(tile);
                } else {
                    entities.emplace_back(tile);
                }

                // handle animation
                std::vector<tson::Tile> animationDetails = spriteSheet->getTiles();

                for(int i = 0; i < animationDetails.size(); i++) {
                    tson::Animation animation = animationDetails[i].getAnimation();
                    if(animation.any()) {
                        std::vector<tson::Frame> tiledFrames = animation.getFrames();
                        std::vector<InputFrame> frames;

                        for(int j = 0; j < tiledFrames.size(); j++) {
                            uint32_t tileId = tiledFrames[j].getTileId();

                            // Get the actual tile referenced by this frame
                            tson::Tile* frameTile = animationDetails[j].getTileset()->getTile(tileId);
                            auto animationSubTexture = frameTile->getDrawingRect();
                            InputFrame inputFrame;

                            inputFrame.sprite.x = animationSubTexture.x;
                            inputFrame.sprite.y = animationSubTexture.y;
                            inputFrame.sprite.w = animationSubTexture.width;
                            inputFrame.sprite.h = animationSubTexture.height;
                            std::cout << inputFrame.sprite.x << " " << inputFrame.sprite.y << std::endl;
                            std::cout << inputFrame.sprite.w << " " << inputFrame.sprite.h << std::endl;

                            inputFrame.duration = (uint8_t)(tiledFrames[j].getDuration() / 100); // convert milliseconds to seconds

                            frames.emplace_back(inputFrame);
                        }

                        AnimatedTile animatedTile(frames);

                        if(layerType == "background") {
                            animatedTile.renderableTexture = &backgroundTiles.back();
                        } else if(layerType == "foreground") {
                            animatedTile.renderableTexture = &foregroundTiles.back();
                        } else {
                            animatedTile.renderableTexture = &entities.back();
                        }
                        animatedTiles.emplace_back(animatedTile);
                    }
                }
            }
        }
    }
    std::vector<RenderableTexture> getBackgroundTiles() { return backgroundTiles; };
    std::vector<RenderableTexture> getForegroundTiles() { return foregroundTiles; };
    std::vector<RenderableTexture> getEntities() { return entities; };
    tson::Colori getBackgroundColor() { return backgroundColor; };
    void update(float timestep) { 
        for(int i = 0; i < animatedTiles.size(); i++) {
            animatedTiles[i].state.update(timestep);
            animatedTiles[i].renderableTexture->subTexture = animatedTiles[i].sprite.getSprite(animatedTiles[i].state);
        } 
    };
private:
    tson::Colori backgroundColor;
    std::vector<Rectangle> collisionObjects;
    Point bounds[4] = {
        {231, 231},
        {231, 570},
        {570, 570},
        {570, 231}
    };
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