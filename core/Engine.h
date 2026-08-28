#ifndef ENGINE_H
#define ENGINE_H

#include "AssetManager.h"
#include "Game.h"
#include "EngineAPI.h"
#include "SDLContext.h"
#include "Window.h"
#include "Renderer.h"
#include "TiledMap.h"

struct SDLDeleter {
    void operator()(SDLContext* context) const {
	    SDL_Quit();
    }
};

class Engine {
public:
    Engine(AssetRegistry& assetRegistry);
    void run(Game& game);
    void loadAssets(const std::string& path);

private:
    void render(Game& game);
    void renderBackground(Game& game, TiledMap& map);
    void renderForeground(Game& game, TiledMap& map);
    void handleOneTimeEvents(Game& game);
    void updateGameState(float timestep, Game& game);
    void sortWorldEntitiesVector();
    void renderWorldEntities(Game& game);
    // void updateLevelInternal(LevelID level);

    std::unique_ptr<SDLContext, SDLDeleter> sdl;
    Window window;
    Renderer renderer;
    AssetManager assets;
    EngineAPI engineAPI;
    AssetRegistry* assetRegistry = nullptr;
    std::vector<RenderableTexture> worldEntitiesVector;
    bool developerMode = false;
    bool running = true;
};

#endif // ENGINE_H