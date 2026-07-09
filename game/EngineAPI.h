#ifndef ENGINEAPI_H
#define ENGINEAPI_H

class AssetManager;

class EngineAPI {
public:
    EngineAPI(AssetManager& assets);
    void requestTexture(int id, const std::string& path);
    void releaseTexture(int id);
private:
    AssetManager& assetManager;
};

#endif // ENGINEAPI_H