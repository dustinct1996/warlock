#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL.h>

#include <unordered_map>
#include <string>
#include <memory>

#include "Utils.h"

struct SDLTextureDeleter {
    void operator()(SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

using TexturePointer = std::unique_ptr<SDL_Texture, SDLTextureDeleter>;

struct Texture {
    TexturePointer texture;
    int refCnt = 0;
};

class AssetManager {
public:
    SDL_Surface* incrementOrCreateSurface(uint32_t id, const std::string& path);
    void addTexture(uint32_t id, SDL_Texture* texture);
    void decrementOrDeleteTexture(uint32_t id);
    SDL_Texture* getTexture(uint32_t id) const;
private:
    void deleteTexture(uint32_t id);
    std::unordered_map<std::string, uint32_t> texturesFilePaths;
    std::unordered_map<uint32_t, Texture> textures;
};

#endif // ASSETMANAGER_H