#include "Window.h"
#include "Logging.h"

Window::Window(
    int w,
    int h,
    int x,
    int y,
    uint32_t flags): window(SDL_CreateWindow(nullptr, x, y, w, h, flags)) {
    if(!window) {
		LOG(ERROR) << "Error creating window: " << SDL_GetError();
		exit(1);
	} else {
        LOG(INFO) << "Success creating window";
    }
}

SDL_Window* Window::getWindow() {
	return window.get();
}

void Window::getWindowSize(int* w, int* h) {
	SDL_GetWindowSize(window.get(), w, h);
}