#include "AssetManager.h"
#include "logging/Logging.h"
#include <filesystem>

AssetManager::~AssetManager() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(std::get<1>(pair.second));
    }
}

void AssetManager::loadGlobalTextures(const std::string& path) {
	if (!std::filesystem::exists(path)) {
		LOG(ERROR) << path << " is not a path that exists";
		return;
	}

    std::string globalTexturesPath = path + "/global_textures";

	for (const auto& entry : std::filesystem::directory_iterator(globalTexturesPath)) {
        if (entry.path().extension() == ".bmp") {
            std::string file = entry.path().string();

			size_t slash = file.find_last_of('/');
			size_t dot = file.find_last_of('.');

			std::string name = file.substr(slash + 1, dot - slash - 1);

			loadTexture(name, AssetScope::GLOBAL, file);
		}
    }
}

void AssetManager::set(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void AssetManager::loadTexture(const std::string& id, const AssetScope& scope, const std::string& path) {
    if (textures.count(id) > 0) {   
        return;
    }

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

    textures[id] = {scope, texture};
    LOG(INFO) << "Success loading " << id << "'s texture";
}

std::tuple<AssetScope, SDL_Texture*> AssetManager::getTexture(const std::string& id) const {
    std::unordered_map<std::string, std::tuple<AssetScope, SDL_Texture*>>::const_iterator it = textures.find(id);

    if(it == textures.end()) {
        LOG(ERROR) << "Texture " << id << " could not be found";
        return {};
    }

    return it->second;
}