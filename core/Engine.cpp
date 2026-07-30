#include <algorithm>
#include "Engine.h"
#include "Utils.h"

Engine::Engine(InitConfig& config, AssetRegistry& assetReg) : assetRegistry(&assetReg), assets(), engineAPI(assets) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		LOG(ERROR) << "Error initializing SDL: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success initializing SDL";
    }

	createWindow(config.windowWidth, config.windowHeight);

	assets.acquireRenderer(renderer);
}

void Engine::createWindow(int width, int height) {
    window = SDL_CreateWindow("Warlock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(!window) {
		LOG(ERROR) << "Error creating window: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success creating window";
    }
    
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetViewport(renderer, nullptr);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(!renderer) {
		LOG(ERROR) << "Error getting renderer: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success getting renderer";
    }
}

void Engine::renderWorldEntities(Game& game) {
	for(int i = 0; i < worldEntitiesVector.size(); i++) {
		SDL_Texture* texture = assets.getTexture(worldEntitiesVector[i].texture);

		float zoom = game.getCamera().getZoom();
		Point cameraPosition = game.getCamera().getPosition();

		int screenPositionX = (int)((worldEntitiesVector[i].worldPosition.x - cameraPosition.x) * zoom);
		int screenPositionY = (int)((worldEntitiesVector[i].worldPosition.y - cameraPosition.y) * zoom);

		SDL_Rect dest;
		int windowWidth;
		int windowHeight;
		
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		dest.w = worldEntitiesVector[i].size.w * zoom;
		dest.h = worldEntitiesVector[i].size.h * zoom;

		dest.x = (screenPositionX - (dest.w / 2)) + (windowWidth / 2);
		dest.y = (screenPositionY - dest.h) + (windowHeight / 2);

		SDL_RenderCopy(renderer, texture, &worldEntitiesVector[i].spriteSheetLocation, &dest);
	}
		
	worldEntitiesVector.clear();
}

void Engine::sortWorldEntitiesVector() {
	std::sort(worldEntitiesVector.begin(), worldEntitiesVector.end(), [](const WorldEntity& a, const WorldEntity& b) {
		return a.worldPosition.y < b.worldPosition.y;
	});
}

void Engine::render(Game& game) {
	// game.getBackgroundTiles();

	// renderBackgroundTiles(game);

	game.getWorldEntities(worldEntitiesVector);

	sortWorldEntitiesVector();
	
	renderWorldEntities(game);

	SDL_RenderPresent(renderer);
}

// void updateLevelInternal(LevelID level) {

// }

void Engine::handleOneTimeEvents(Game& game) {
	SDL_Event e;
	
	while(SDL_PollEvent(&e) != 0) {
		switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if(e.key.keysym.sym == SDLK_F1) {
#ifdef DEVELOPER_BUILD
					if(!developerMode) {
						LOG(INFO) << "Entering developer mode";
						developerMode = true;
					} else {
						LOG(INFO) << "Exiting developer mode";
						developerMode = false;
					}
#endif
				}
				break;
			case SDL_MOUSEWHEEL:
				if(SDL_GetModState() & KMOD_CTRL) {
					// Scroll away
					if(e.wheel.y > 0) {
						game.getCamera().updateZoom(1);
					}
					// Scroll toward
					if(e.wheel.y < 0) {
						game.getCamera().updateZoom(-1);
					}
				}
			break;
		}
	}
}

void Engine::updateGameState(float timestep, Game& game) {
	const unsigned char* keys = SDL_GetKeyboardState(NULL);
	game.update(keys, timestep);
}

void Engine::run(Game& game) {
	game.init(engineAPI);
	
	auto previous = std::chrono::steady_clock::now();

	while(running) {
		// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		auto current = std::chrono::steady_clock::now();
		
		float timestep = std::chrono::duration<float>(current - previous).count();

		previous = current;

		SDL_RenderClear(renderer);
		
		handleOneTimeEvents(game);

		updateGameState(timestep, game);

		render(game);
	}
}

Engine::~Engine() {
    LOG(INFO) << "Destroying SDL window";
    SDL_DestroyWindow(window);
    LOG(INFO) << "Quitting program";
	SDL_Quit();
}