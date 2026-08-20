#include <SDL.h>
#include <memory>

struct SDLRendererDeleter {
    void operator()(SDL_Renderer* renderer) const {
        SDL_DestroyRenderer(renderer);
    }
};

class Renderer {
public:
    Renderer(
        SDL_Window* window,
        int index = -1,
        uint32_t flags = SDL_RENDERER_ACCELERATED,
        const SDL_Rect* viewport = nullptr,
        uint8_t r = 255,
        uint8_t g = 255,
        uint8_t b = 255,
        uint8_t a = 255
    );
    void copyToRenderer(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect);
    void clear();
    void render();
    void setRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    SDL_Texture* createTexture(SDL_Surface* surface);
private:
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer;
};