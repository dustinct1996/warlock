#include "AssetManager.h"
#include <filesystem>

SDL_Surface* AssetManager::incrementOrCreateSurface(uint32_t id, const std::string& path) {
    if(textures.count(id) > 0) {   
        textures[id].refCnt++;
		return nullptr;
    }
	
	SDL_Surface* surface;

	std::string extension;

	// check file type
	for(int i = 0; i < path.size(); i++) {
		if(path[i] == '.') {
			extension.clear();
		}

		extension += path[i];
	}
	
	if(extension == ".bmp") {
		surface = SDL_LoadBMP(path.c_str());
	} else if(extension == ".png") {
		// add .png support
	}

	if(!surface) {
		LOG(ERROR) << "Error loading " << id << "'s image: " << SDL_GetError();
		exit(1);
	}

	return surface;
}

void AssetManager::decrementOrDeleteTexture(uint32_t id) {
    if(textures.count(id) > 0 && textures[id].refCnt > 1) {   
        textures[id].refCnt--;
    } else {
		deleteTexture(id);
	}
}

void AssetManager::addTexture(uint32_t id, SDL_Texture* texture) {
	textures[id].texture = TexturePointer(texture);
	LOG(INFO) << "Success loading " << id << "'s texture";
}

void AssetManager::deleteTexture(uint32_t id) {
	textures.erase(id);
	LOG(INFO) << "Success deleting " << id << "'s texture";
}

SDL_Texture* AssetManager::getTexture(uint32_t id) const {
    std::unordered_map<uint32_t, Texture>::const_iterator it = textures.find(id);

    if(it == textures.end()) {
        LOG(ERROR) << "Texture " << id << " could not be found";
        return {};
    }

    return it->second.texture.get();
}