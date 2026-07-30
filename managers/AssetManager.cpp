#include "AssetManager.h"
#include <filesystem>

void AssetManager::acquireRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void AssetManager::incrementOrLoadTexture(unsigned int id, const std::string& path) {
    if (textures.count(id) > 0) {   
        textures[id].refCnt++;
    } else {
		loadTexture(id, path);
	}
}

void AssetManager::decrementOrDeleteTexture(unsigned int id) {
    if (textures.count(id) > 0 && textures[id].refCnt > 1) {   
        textures[id].refCnt--;
    } else {
		deleteTexture(id);
	}
}

void AssetManager::loadTexture(unsigned int id, const std::string& path) {
	SDL_Surface *surface;

	surface = SDL_LoadBMP(path.c_str());

	if (!surface) {
		LOG(ERROR) << "Error loading " << id << "'s image: " << SDL_GetError();
		exit(1);
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	if (!texture) {
		LOG(ERROR) << "Error converting " << id << "'s surface: " << SDL_GetError();
		exit(1);
	}

	textures[id].texture = TexturePtr(texture);
	LOG(INFO) << "Success loading " << id << "'s texture";
}

void AssetManager::deleteTexture(unsigned int id) {
	textures.erase(id);
	LOG(INFO) << "Success deleting " << id << "'s texture";
}

SDL_Texture* AssetManager::getTexture(unsigned int id) const {
    std::unordered_map<unsigned int, Texture>::const_iterator it = textures.find(id);

    if(it == textures.end()) {
        LOG(ERROR) << "Texture " << id << " could not be found";
        return {};
    }

    return it->second.texture.get();
}