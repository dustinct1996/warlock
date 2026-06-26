#pragma once

#include "AssetManager.h"
#include "Game.h"

class Engine {
public:
    Engine(InitConfig& config);
    ~Engine();
    void run(Game& game);
    void loadAssets(const std::string& path);

private:
    void init(InitConfig& config);
    void createWindow();
    SDL_Window* window;
    SDL_Renderer* renderer;
    AssetManager assets;
    bool developerMode = false;
    bool running = true;
    std::vector<RenderItem> renderItemsBuffer;
};