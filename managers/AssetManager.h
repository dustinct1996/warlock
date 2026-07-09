#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL.h>

#include <unordered_map>
#include <string>

#include "Utils.h"

enum class TextureType {
    CONSTANT,
    LEVEL
};

struct Texture {
    SDL_Texture* texture;
    int refCnt = 0;
};

class AssetManager {
public:
    AssetManager(SDL_Renderer* renderer);
    ~AssetManager();
    void incrementOrLoadTexture(int id, const std::string& path);
    void decrementOrDeleteTexture(int id);
    SDL_Texture* getTexture(int id) const;
private:
    void loadTexture(int id, const std::string& path);
    void deleteTexture(int id);
    SDL_Renderer* renderer;
    std::unordered_map<int, Texture> textures;
};

#endif // ASSETMANAGER_H