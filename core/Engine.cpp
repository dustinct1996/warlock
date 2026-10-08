#include <algorithm>
#include <optional>
#include "Engine.h"
#include "Utils.h"

Engine::Engine(/*AssetRegistry& assetReg*/):
	sdl(),
	window(1280, 720),
	renderer(window.getWindow()),
	assets(),
	engineAPI(renderer, assets)/*,
	assetRegistry(&assetReg)*/ {}

void Engine::renderRenderableEntities(Game& game) {
	for(uint32_t i = 0; i < renderableEntitiesVector.size(); i++) {
		SDL_Texture* texture = assets.getTexture(renderableEntitiesVector[i].texture);

		float zoom = game.getCamera().getZoom();
		Point cameraPosition = game.getCamera().getPosition();
		
		renderer.setRenderDrawColor(0, 0, 0, 255);
		uint32_t screenPositionX = (uint32_t)((renderableEntitiesVector[i].position.x - cameraPosition.x) * zoom);
		uint32_t screenPositionY = (uint32_t)((renderableEntitiesVector[i].position.y - cameraPosition.y) * zoom);

		Rectangle dest;
		int windowWidth;
		int windowHeight;
		
		window.getWindowSize(&windowWidth, &windowHeight);

		dest.w = renderableEntitiesVector[i].size.w * zoom;
		dest.h = renderableEntitiesVector[i].size.h * zoom;

		dest.x = (screenPositionX - (dest.w / 2)) + (windowWidth / 2);
		dest.y = (screenPositionY - dest.h) + (windowHeight / 2);

		renderer.copyTextureToRenderer(
			texture, 
			&renderableEntitiesVector[i].subTexture, 
			&dest,
			renderableEntitiesVector[i].rotation,
			renderableEntitiesVector[i].rotationAxis.has_value() ? &renderableEntitiesVector[i].rotationAxis.value() : nullptr,
			renderableEntitiesVector[i].reflection
		);
	}
		
	renderableEntitiesVector.clear();







	for(uint32_t i = 0; i < actors.size(); i++) {
		Point position;
		int windowWidth;
		int windowHeight;

		Graphic& graphic = actors[i]->getGraphic();
		float zoom = game.getCamera().getZoom();
		Point cameraPosition = game.getCamera().getPosition();
		window.getWindowSize(&windowWidth, &windowHeight);

		uint32_t screenPositionX = (uint32_t)((actors[i]->getPosition().x - cameraPosition.x) * zoom);
		uint32_t screenPositionY = (uint32_t)((actors[i]->getPosition().y - cameraPosition.y) * zoom);

		position.x = screenPositionX + (windowWidth / 2);
		position.y = screenPositionY + (windowHeight / 2);

		graphic.render(renderer, position, zoom, &assets);
	}

	actors.clear();
}

void Engine::renderBackground(Game& game, TiledMap& map) {
	float zoom = game.getCamera().getZoom();
	Point cameraPosition = game.getCamera().getPosition();

	std::vector<RenderableTexture> backgroundTiles = map.getBackgroundTiles();

	for(int i = 0; i < backgroundTiles.size(); i++) {
		SDL_Texture* texture = assets.getTexture(backgroundTiles[i].texture);
		uint32_t screenPositionX = (uint32_t)((backgroundTiles[i].position.x - cameraPosition.x) * zoom);
		uint32_t screenPositionY = (uint32_t)((backgroundTiles[i].position.y - cameraPosition.y) * zoom);

		Rectangle dest;
		int windowWidth;
		int windowHeight;
		
		window.getWindowSize(&windowWidth, &windowHeight);

		dest.w = backgroundTiles[i].size.w * zoom;
		dest.h = backgroundTiles[i].size.h * zoom;

		dest.x = (screenPositionX - (dest.w / 2)) + (windowWidth / 2);
		dest.y = (screenPositionY - dest.h) + (windowHeight / 2);

		renderer.copyTextureToRenderer(
			texture, 
			&backgroundTiles[i].subTexture, 
			&dest,
			backgroundTiles[i].rotation,
			backgroundTiles[i].rotationAxis.has_value() ? &backgroundTiles[i].rotationAxis.value() : nullptr,
			backgroundTiles[i].reflection
		);
	}
}

void Engine::renderForeground(Game& game, TiledMap& map) {
	float zoom = game.getCamera().getZoom();
	Point cameraPosition = game.getCamera().getPosition();

	std::vector<RenderableTexture> foregroundTiles = map.getForegroundTiles();

	for(int i = 0; i < foregroundTiles.size(); i++) {
		SDL_Texture* texture = assets.getTexture(foregroundTiles[i].texture);
		uint32_t screenPositionX = (uint32_t)((foregroundTiles[i].position.x - cameraPosition.x) * zoom);
		uint32_t screenPositionY = (uint32_t)((foregroundTiles[i].position.y - cameraPosition.y) * zoom);

		Rectangle dest;
		int windowWidth;
		int windowHeight;
		
		window.getWindowSize(&windowWidth, &windowHeight);

		dest.w = foregroundTiles[i].size.w * zoom;
		dest.h = foregroundTiles[i].size.h * zoom;

		dest.x = (screenPositionX - (dest.w / 2)) + (windowWidth / 2);
		dest.y = (screenPositionY - dest.h) + (windowHeight / 2);

		renderer.copyTextureToRenderer(
			texture, 
			&foregroundTiles[i].subTexture, 
			&dest,
			foregroundTiles[i].rotation,
			foregroundTiles[i].rotationAxis.has_value() ? &foregroundTiles[i].rotationAxis.value() : nullptr,
			foregroundTiles[i].reflection
		);
	}
}

void Engine::sortRenderableEntitiesVector() {
	std::sort(renderableEntitiesVector.begin(), renderableEntitiesVector.end(), [](const RenderableTexture& a, const RenderableTexture& b) {
		return a.position.y < b.position.y;
	});
}

void Engine::render(Game& game) {
	TiledMap& map = game.getCurrentMap();

	renderBackground(game, map);

	game.getRenderableActors(actors);

	std::vector<RenderableTexture> mapEntities = map.getEntities();

	renderableEntitiesVector.insert(renderableEntitiesVector.end(), mapEntities.begin(), mapEntities.end());

	sortRenderableEntitiesVector();
	
	renderRenderableEntities(game);

	renderForeground(game, map);

	auto drawColor = map.getBackgroundColor();

	renderer.setRenderDrawColor(drawColor.r, drawColor.g, drawColor.b, drawColor.a);

	renderer.render();
}

// void updateLevelInternal(LevelID level) {

// }

void Engine::pollEvent(Game& game) {
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
						game.getCamera().increaseZoom();
					}
					// Scroll toward
					if(e.wheel.y < 0) {
						game.getCamera().decreaseZoom();
					}
				}
			break;
		}
	}
}

void Engine::updateState(float timestep, Game& game) {
	const unsigned char* keys = SDL_GetKeyboardState(NULL);
	game.update(keys, timestep);
}

void Engine::run(Game& game) {
	game.init(engineAPI);
	
	auto previous = std::chrono::steady_clock::now();

	while(running) {
		auto current = std::chrono::steady_clock::now();
		
		float timestep = std::chrono::duration<float>(current - previous).count();

		previous = current;

		renderer.clear();
		
		pollEvent(game);

		updateState(timestep, game);

		render(game);
	}
}