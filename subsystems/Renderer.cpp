#include "Renderer.h"
#include "Logging.h"

Renderer::Renderer(
	SDL_Window* window,
	int index,
	uint32_t flags,
	const SDL_Rect* viewport,
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t a): renderer(SDL_CreateRenderer(window, index, flags)) {
	SDL_RenderSetViewport(renderer.get(), viewport);
	SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);

    if(!renderer.get()) {
		LOG(ERROR) << "Error creating renderer: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success creating renderer";
    }
}

void Renderer::copyToRenderer(
	SDL_Texture* texture,
	Rectangle* subTexture,
	Rectangle* rendererPortion,
	double rotation,
	Point* rotationAxis,
	Reflection reflection) {
    SDL_Rect SDLSubTexture;
    SDL_Rect SDLRendererPortion;
    SDL_Point SDLRotationAxis;

    if (subTexture != nullptr) {
        SDLSubTexture = {
            subTexture->x,
            subTexture->y,
            subTexture->w,
            subTexture->h
        };
    }

    if (rendererPortion != nullptr) {
        SDLRendererPortion = {
            rendererPortion->x,
            rendererPortion->y,
            rendererPortion->w,
            rendererPortion->h
        };
    }

    if (rotationAxis != nullptr) {
        SDLRotationAxis = {
            rotationAxis->x,
            rotationAxis->y
        };
    }

	SDL_RenderCopyEx(
		renderer.get(), 
		texture, 
		subTexture != nullptr ? &SDLSubTexture : nullptr, 
		rendererPortion != nullptr ? &SDLRendererPortion : nullptr, 
		rotation, 
		rotationAxis != nullptr ? &SDLRotationAxis : nullptr, 
		(reflection != Reflection::NONE ? (reflection == Reflection::VERTICAL ? SDL_FLIP_VERTICAL : SDL_FLIP_HORIZONTAL) : SDL_FLIP_NONE));
}

void Renderer::clear() {
    SDL_RenderClear(renderer.get());
}

void Renderer::render() {
    SDL_RenderPresent(renderer.get());
}

void Renderer::setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
}

SDL_Texture* Renderer::createTexture(SDL_Surface* surface) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface);

	SDL_FreeSurface(surface);

	if (!texture) {
		LOG(ERROR) << "Error converting surface: " << SDL_GetError();
		exit(1);
	}

    return texture;
}