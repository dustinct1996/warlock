#ifndef GAME_H
#define GAME_H

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Utils.h"
#include "Actor.h"
#include "EngineAPI.h"
#include "Camera.h"
#include "SpriteSheet.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "TiledMap.h"

struct AssetRegistry {
    std::unordered_map<uint32_t, std::unique_ptr<SpriteSheet>> spriteSheets;
};

class Game {
public:
    Game() = default;
    virtual ~Game() = default;
    virtual void init(EngineAPI& engineAPI) = 0;
    virtual void update(const unsigned char* keys, float timestep) = 0;
    virtual void getRenderableEntities(std::vector<RenderableTexture>& renderableEntitiesVector) = 0;
    virtual void getRenderableActors(std::vector<Actor*>& actors) = 0;
    // void addSpriteSheet(
    //     uint32_t spriteSheetID, 
    //     std::string pathToTexture, 
    //     uint16_t spriteSizeX, 
    //     uint16_t spriteSizeY, 
    //     uint8_t spriteOffset = 0, 
    //     uint8_t sheetMargin = 0) {
    //     assetRegistry.spriteSheets[TextureID::VILLAGE] = std::make_unique<SpriteSheet>(
    //         TextureID::VILLAGE, "assets/textures/level_one/village.bmp", 16, 16, 1, 0);
    // }
    virtual TiledMap& getCurrentMap() = 0;
    virtual Camera& getCamera() = 0; // TODO: This forces developers to only have one Camera. Make it so they can have as many as they want.
    virtual AssetRegistry& getAssetRegistry() = 0;

protected:
    EngineAPI* engineAPI = nullptr;
    AssetRegistry assetRegistry;
    std::vector<std::unique_ptr<Actor>> renderableEntities;
    EntityManager entityManager;
    // CollisionManager collisionManager;
};

#endif // GAME_H