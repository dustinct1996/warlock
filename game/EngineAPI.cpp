#include "EngineAPI.h"
#include "AssetManager.h"

EngineAPI::EngineAPI(AssetManager& assets) {
    assetManager = assets;
}

void EngineAPI::requestTexture(int id, const std::string& path) {
    assetManager.incrementOrLoadTexture(id, path);
}

void EngineAPI::releaseTexture(int id) {
    assetManager.decrementOrDeleteTexture(id);
}