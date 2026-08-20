#ifndef ENGINEAPI_H
#define ENGINEAPI_H

#include <string>

class AssetManager;
class Renderer;

class EngineAPI {
public:
    EngineAPI(Renderer& sdlRenderer, AssetManager& assets);
    void requestTexture(uint32_t id, const std::string& path);
    void releaseTexture(uint32_t id);
private:
    Renderer* renderer;
    AssetManager* assetManager;
};

#endif // ENGINEAPI_H