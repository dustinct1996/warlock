#include <SDL.h>
#include "EngineAPI.h"
#include "AssetManager.h"
#include "Renderer.h"

EngineAPI::EngineAPI(Renderer& sdlRenderer, AssetManager& assets) : renderer(&sdlRenderer), assetManager(&assets) {}

void EngineAPI::requestTexture(uint32_t id, const std::string& path) {
    SDL_Surface* surface = assetManager->incrementOrCreateSurface(id, path);
    SDL_Texture* texture = renderer->createTexture(surface);
    assetManager->addTexture(id, texture);
}

void EngineAPI::releaseTexture(uint32_t id) {
    assetManager->decrementOrDeleteTexture(id);
}