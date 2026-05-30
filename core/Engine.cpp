#include "Engine.h"
#include "logging/Logging.h"
#include <chrono>

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

	// init camera
	// SDL_GetWindowSize(window, &camera.w, &camera.h);
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

    if (!renderer) {
		LOG(ERROR) << "Error getting renderer: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success getting renderer";
    }
}

void Engine::run(Game& game) {		
	game.init();
	int cnt = 1;
	double sum = 0;

	while(running) {
		auto start = std::chrono::system_clock::now();
		auto duration = start.time_since_epoch();
		auto startSeconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
		// clear screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		
		renderItemsBuffer.clear();
	

		// update game state
		SDL_Event e;
		while(SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_WINDOWEVENT:
					switch (e.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							SDL_RenderSetViewport(renderer, NULL);
							
							// reset camera
							// SDL_GetWindowSize(window, &camera.w, &camera.h);
							break;
					}
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
			}
		}
		const unsigned char* keys = SDL_GetKeyboardState(NULL);
		game.update(keys);

		// grab global texture IDs and pass into asset manager
		game.getRenderItems(renderItemsBuffer);

		// copy all sprites into renderer
		for(int i = 0; i < renderItemsBuffer.size(); i++) {
			SDL_Texture* texture = std::get<1>(assets.getTexture(renderItemsBuffer[i].texture));
			SDL_Rect dest;
			dest.x = (int)renderItemsBuffer[i].position.x;
			dest.y = (int)renderItemsBuffer[i].position.y;
			// LOG(INFO) << dest.x << " " << dest.y;
			dest.h = renderItemsBuffer[i].size.h;
			dest.w = renderItemsBuffer[i].size.w;

			SDL_RenderCopy(renderer, texture, NULL, &dest);
		}

		SDL_RenderPresent(renderer);
		
		auto end = std::chrono::system_clock::now();
		duration = end.time_since_epoch();
		auto endSeconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
		sum += (endSeconds - startSeconds);

		if (cnt == 750) {
			LOG(INFO) << sum / 750;
			sum = 0;
			cnt = 0;
		}
		cnt++;
	}
}

Engine::~Engine() {
    LOG(INFO) << "Destroying SDL window";
    SDL_DestroyWindow(window);
    LOG(INFO) << "Quitting program";
	SDL_Quit();
}