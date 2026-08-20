#ifndef TILEDMAP_H
#define TILEDMAP_H

#include "tileson.hpp"
#include "Logging.h"
#include "Structs.h"
#include "SpriteSheet.h"

class TiledMap {
public:
    TiledMap(std::vector<SpriteSheet*> spriteSheets) {
        this->spriteSheets = spriteSheets;

        tson::Tileson t;
        std::unique_ptr<tson::Map> map = t.parse("assets/maps/DevMap.tmj");
        backgroundColor = map->getBackgroundColor();

        for (auto& layer : map->getLayers()) {
            if(layer.getName() == "collision") {
                for(auto& object : layer.getObjects()) {
                    if(object.getObjectType() == tson::ObjectType::Rectangle) {
                        tson::Vector2i position = object.getPosition();
                        tson::Vector2i size = object.getSize();
                        SDL_Rect collisionBox;
                        collisionBox.x = position.x;
                        collisionBox.y = position.y;
                        collisionBox.w = size.x;
                        collisionBox.h = size.y;
                        collisionObjects.emplace_back(collisionBox);
                    }
                }
            } else {
                for(auto &[pos, tileObject] : layer.getTileObjects()) {
                    std::string layerType = 
                        std::any_cast<std::string>(layer.getProperties().getProperty("layer")->getValue());

                    WorldEntity worldEntity;
                    worldEntity.worldPosition.x = tileObject.getPosition().x;
                    worldEntity.worldPosition.y = tileObject.getPosition().y;
                    worldEntity.size.w = tileObject.getTile()->getTileSize().x;
                    worldEntity.size.h = tileObject.getTile()->getTileSize().y;

                    std::string spriteSheetPath = tileObject.getTile()->getTileset()->getImage().u8string();
                    tson::Rect locationInPixels = tileObject.getDrawingRect();
                    
                    for(int i = 0; i < spriteSheets.size(); i++) {
                        if(spriteSheets[i]->getPath().substr(6) == spriteSheetPath.substr(2)) {
                            worldEntity.texture = spriteSheets[i]->getTextureID();

                            uint8_t offset = spriteSheets[i]->getOffset();
                            uint8_t margin = spriteSheets[i]->getMargin();

                            LOG(INFO) << locationInPixels.x;
                            LOG(INFO) << locationInPixels.y;

                            worldEntity.spriteSheetLocation.x = locationInPixels.x;
                            worldEntity.spriteSheetLocation.y = locationInPixels.y;
                            worldEntity.spriteSheetLocation.w = locationInPixels.width;
                            worldEntity.spriteSheetLocation.h = locationInPixels.height;
                        }
                    }

                    if(layerType == "background") {
                        backgroundTiles.emplace_back(worldEntity);
                    } else if(layerType == "foreground") {
                        foregroundTiles.emplace_back(worldEntity);
                    } else {
                        entities.emplace_back(worldEntity);
                    }
                }
            }
        }
    }

    std::vector<WorldEntity> getBackgroundTiles() { return backgroundTiles; };
    std::vector<WorldEntity> getForegroundTiles() { return foregroundTiles; };
    std::vector<WorldEntity> getEntities() { return entities; };
    tson::Colori getBackgroundColor() { return backgroundColor; };
private:
    tson::Colori backgroundColor;
    std::vector<SDL_Rect> collisionObjects;
    Point bounds[4] = {
        {231, 231},
        {231, 570},
        {570, 570},
        {570, 231}
    };
    std::vector<WorldEntity> backgroundTiles;
    std::vector<WorldEntity> foregroundTiles;
    std::vector<WorldEntity> entities;
    Size tileSize = {16, 16};
    std::vector<SpriteSheet*> spriteSheets;
};

#endif // TILEDMAP_H