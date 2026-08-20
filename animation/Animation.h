#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL.h>
#include "AnimationState.h"

struct InputFrame {
    SDL_Rect sprite;
    uint8_t duration;
};

struct AnimationFrame {
    SDL_Rect sprite;
    uint8_t triggerFrame;
};

class Animation {
public:
    Animation(std::vector<InputFrame> entityPayload);
    SDL_Rect getSprite(AnimationState& state);
private:
    std::vector<AnimationFrame> frames;
    uint8_t totalFrames = 0;
};

#endif // ANIMATION_H