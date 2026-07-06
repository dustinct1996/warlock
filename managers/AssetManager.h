#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL.h>

#include <unordered_map>
#include <string>

#include "Utils.h"

class AssetManager {
public:
    ~AssetManager();
    void loadTextures(const std::string& path);
    void set(SDL_Renderer* renderer);
    void loadTexture(const std::string& id, const std::string& path);
    SDL_Texture* getTexture(const std::string& id) const;
private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> textures;
};

#endif // ASSETMANAGER_H