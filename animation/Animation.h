#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL.h>
#include "AnimationState.h"

struct InputFrame {
    SDL_Rect sprite;
    unsigned char duration;
};

struct AnimationFrame {
    SDL_Rect sprite;
    unsigned char triggerFrame;
};

class Animation {
public:
    Animation(std::vector<InputFrame> entityPayload);
    SDL_Rect getSprite(AnimationState& state);
private:
    std::vector<AnimationFrame> frames_;
    unsigned char totalFrames_ = 0;
};

#endif // ANIMATION_H