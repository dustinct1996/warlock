#include <SDL.h>
#include <memory>

struct SDLWindowDeleter {
    void operator()(SDL_Window* window) const {
        SDL_DestroyWindow(window);
    }
};

class Window {
public:
    Window(
        int w,
        int h,
        int x = SDL_WINDOWPOS_UNDEFINED,
        int y = SDL_WINDOWPOS_UNDEFINED,
        uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    SDL_Window* getWindow();
    void getWindowSize(int* w, int* h);
private:
    std::unique_ptr<SDL_Window, SDLWindowDeleter> window;
};