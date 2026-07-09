#ifndef ENGINE_H
#define ENGINE_H

#include "AssetManager.h"
#include "Game.h"
#include "EngineAPI.h"

class Engine {
public:
    Engine(InitConfig& config, AssetRegistry& assetRegistry);
    ~Engine();
    void run(Game& game);
    void loadAssets(const std::string& path);

private:
    void createWindow(int width, int height);
    void render(Game& game);
    void handleOneTimeEvents(Game& game);
    void handleGameEvents(float timestep, Game& game);
    void sortRenderItemsBuffer();
    void renderEntities(Game& game);
    // void updateLevelInternal(LevelID level);

    SDL_Window* window;
    SDL_Renderer* renderer;
    AssetManager assets;
    std::vector<RenderItem> renderItemsBuffer;
    bool developerMode = false;
    bool running = true;
    AssetRegistry* assetRegistry = nullptr;
    EngineAPI engineAPI;
    // LevelID currentLevel;
};

#endif // ENGINE_H