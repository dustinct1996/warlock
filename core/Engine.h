#ifndef ENGINE_H
#define ENGINE_H

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
    void handleGameEvents(float timestep, Game& game);
    void sortRenderItemsBuffer();
    void renderEntities(Game& game);
    void loadTextures(const std::string& path);

    SDL_Window* window;
    SDL_Renderer* renderer;
    AssetManager assets;
    std::vector<RenderItem> renderItemsBuffer;
    bool developerMode = false;
    bool running = true;
};

#endif // ENGINE_H