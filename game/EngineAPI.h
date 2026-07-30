#ifndef ENGINEAPI_H
#define ENGINEAPI_H

#include <string>

class AssetManager;

class EngineAPI {
public:
    EngineAPI(AssetManager& assets);
    void requestTexture(unsigned int id, const std::string& path);
    void releaseTexture(unsigned int id);
private:
    AssetManager* assetManager;
};

#endif // ENGINEAPI_H