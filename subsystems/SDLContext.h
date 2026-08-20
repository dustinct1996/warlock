#include <SDL.h>

class SDLContext {
public:
    SDLContext(uint32_t flags = SDL_INIT_EVERYTHING) {
        if(SDL_Init(flags) < 0) {
            LOG(ERROR) << "Error initializing SDL: " << SDL_GetError();
            exit(1);
        } else {
            LOG(INFO) << "Success initializing SDL";
        }
    }
};