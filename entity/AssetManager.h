#include <SDL.h>
#include <unordered_map>
#include <string>

enum class AssetScope {
    GLOBAL,
    LEVEL,
    SCENE
};

class AssetManager {
public:
    ~AssetManager();
    void loadGlobalTextures(const std::string& path);
    void set(SDL_Renderer* renderer);
    void loadTexture(const std::string& id, const AssetScope& scope, const std::string& path);
    std::tuple<AssetScope, SDL_Texture*> getTexture(const std::string& id) const;
private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, std::tuple<AssetScope, SDL_Texture*>> textures;
};