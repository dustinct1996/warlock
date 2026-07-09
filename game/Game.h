#ifndef GAME_H
#define GAME_H

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Utils.h"
#include "Entity.h"
#include "EngineAPI.h"
#include "Camera.h"

using AssetID = int;

struct InitConfig {
    int windowWidth;
    int windowHeight;
};

struct AssetRegistry {
    std::unordered_map<AssetID, std::string /* pathToAsset */> textureRegistry;
};

class Game {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Game() = default;
    virtual ~Game() = default;
    virtual void init() = 0;
    virtual void update(const unsigned char* keys, float timestep) = 0;
    virtual void getRenderItems(std::vector<RenderItem>& renderItemsBuffer) = 0;
    virtual Camera& getCamera() = 0; // TODO: This forces developers to only have one Camera. Make it so they can have as many as they want.
    virtual AssetRegistry& getAssetRegistry() = 0;
    virtual InitConfig& getInitConfig() = 0;
    inline void acquireEngineAPI(EngineAPI& engineAPI) {
        this->engineAPI = &engineAPI;
    }

protected:
    EngineAPI* engineAPI;
    AssetRegistry assetRegistry;
    std::vector<std::unique_ptr<Entity>> renderEntities;
};

#endif // GAME_H