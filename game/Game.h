#ifndef GAME_H
#define GAME_H

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Utils.h"
#include "Entity.h"
#include "EngineAPI.h"
#include "Camera.h"
#include "SpriteSheet.h"

struct InitConfig {
    int windowWidth;
    int windowHeight;
};

struct AssetRegistry {
    std::unordered_map<int /* id */, std::unique_ptr<SpriteSheet>> spriteSheets;
};

class Game {
public:
    Game() = default;
    virtual ~Game() = default;
    virtual void init(EngineAPI& engineAPI) = 0;
    virtual void update(const unsigned char* keys, float timestep) = 0;
    virtual void getWorldEntities(std::vector<WorldEntity>& worldEntitiesVector) = 0;
    virtual Camera& getCamera() = 0; // TODO: This forces developers to only have one Camera. Make it so they can have as many as they want.
    virtual AssetRegistry& getAssetRegistry() = 0;
    virtual InitConfig& getInitConfig() = 0;

protected:
    EngineAPI* p_engineAPI = nullptr;
    AssetRegistry assetRegistry;
    std::vector<std::unique_ptr<Entity>> worldEntities;
};

#endif // GAME_H