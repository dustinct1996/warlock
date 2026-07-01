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
    void createWindow(int width, int height);
    void render(Game& game);
    void handleOneTimeEvents(Game& game);
    void handleKeyboardStateEvents(float timestep, Game& game);
    SDL_Window* window;
    SDL_Renderer* renderer;
    AssetManager assets;
    bool developerMode = false;
    bool running = true;
    std::vector<RenderItem> renderItemsBuffer;
};