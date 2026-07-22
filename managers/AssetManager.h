#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL.h>

#include <unordered_map>
#include <string>
#include <memory>

#include "Utils.h"

struct TextureDeleter {
    void operator()(SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

struct Texture {
    TexturePtr texture;
    int refCnt = 0;
};

class AssetManager {
public:
    void acquireRenderer(SDL_Renderer* renderer);
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