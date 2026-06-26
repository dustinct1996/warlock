#include "Engine.h"
#include "Include.h"

Engine::Engine(InitConfig& config) {
    init(config);
}

void Engine::init(InitConfig& config) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		LOG(ERROR) << "Error initializing SDL: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success initializing SDL";
    }

	createWindow();

	// init assetManager
	assets.set(renderer); // TODO: should renderer be a shared_ptr?

	assets.loadGlobalTextures(config.assetsLocation);

	assets.loadLevelTextures(config.assetsLocation);
}

void Engine::createWindow() {
    window = SDL_CreateWindow("Warlock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
		LOG(ERROR) << "Error creating window: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success creating window";
    }
    
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetViewport(renderer, nullptr);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if (!renderer) {
		LOG(ERROR) << "Error getting renderer: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success getting renderer";
    }
}

void Engine::run(Game& game) {		
	game.init();
	
	long start;

	while(running) {
		float timestep = 
			std::chrono::duration_cast<std::chrono::milliseconds>(
    			std::chrono::steady_clock::now().time_since_epoch()
			).count() - start;
		start = std::chrono::duration_cast<std::chrono::milliseconds>(
    				std::chrono::steady_clock::now().time_since_epoch()
				).count();

		SDL_RenderClear(renderer);
		
		renderItemsBuffer.clear();

		SDL_Event e;
		while(SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_F1) {
	#ifdef DEVELOPER_BUILD
						if (!developerMode) {
							LOG(INFO) << "Entering developer mode";
							developerMode = true;
						} else {
							LOG(INFO) << "Entering standard mode";
							developerMode = false;
						}
	#endif
					}
					break;
				case SDL_MOUSEWHEEL:
					if (SDL_GetModState() & KMOD_CTRL) {
						// Scroll away
						if (e.wheel.y > 0) {
							game.camera.updateZoom(0.16);
						}
						// Scroll toward
						if (e.wheel.y < 0) {
							LOG(INFO) << "Zooming out";
							game.camera.updateZoom(-0.16);
						}
					}
				break;
			}
		}
		const unsigned char* keys = SDL_GetKeyboardState(NULL);
		game.update(keys, timestep);

		game.getRenderItems(renderItemsBuffer);
		// "../../../assets/level_textures/rock"

		SDL_Texture* texture = std::get<1>(assets.getTexture("rock"));
		SDL_Rect dest;
		float zoom = game.camera.getZoom();
		int windowWidth;
		int windowHeight;
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		dest.x = ((300 - game.camera.getPosition().x) * (zoom == 0 ? 0.1 : zoom)) + (windowWidth / 2);
		dest.y = ((300 - game.camera.getPosition().y) * (zoom == 0 ? 0.1 : zoom)) + (windowHeight / 2);
		dest.h = 56 * (zoom == 0 ? 0.1 : zoom);
		dest.w = 56 * (zoom == 0 ? 0.1 : zoom);

		SDL_RenderCopy(renderer, texture, NULL, &dest);

		for(int i = 0; i < renderItemsBuffer.size(); i++) {
			SDL_Texture* texture = std::get<1>(assets.getTexture(renderItemsBuffer[i].texture));
			SDL_Rect dest;
			float zoom = game.camera.getZoom();
			int windowWidth;
			int windowHeight;
			SDL_GetWindowSize(window, &windowWidth, &windowHeight);

			dest.x = (((int)renderItemsBuffer[i].position.x - game.camera.getPosition().x) * (zoom == 0 ? 0.1 : zoom)) + (windowWidth / 2);
			dest.y = (((int)renderItemsBuffer[i].position.y - game.camera.getPosition().y) * (zoom == 0 ? 0.1 : zoom)) + (windowHeight / 2);
			dest.h = renderItemsBuffer[i].size.h * (zoom == 0 ? 0.1 : zoom);
			dest.w = renderItemsBuffer[i].size.w * (zoom == 0 ? 0.1 : zoom);

			SDL_RenderCopy(renderer, texture, NULL, &dest);
		}

		SDL_RenderPresent(renderer);
	}
}

Engine::~Engine() {
    LOG(INFO) << "Destroying SDL window";
    SDL_DestroyWindow(window);
    LOG(INFO) << "Quitting program";
	SDL_Quit();
}