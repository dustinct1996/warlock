#include "EngineAPI.h"
#include "AssetManager.h"

EngineAPI::EngineAPI(AssetManager& assets) : assetManager(&assets) {}

void EngineAPI::requestTexture(unsigned int id, const std::string& path) {
    assetManager->incrementOrLoadTexture(id, path);
}

void EngineAPI::releaseTexture(unsigned int id) {
    assetManager->decrementOrDeleteTexture(id);
}