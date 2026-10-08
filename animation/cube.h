#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SDL.h>
#include "Utils.h"
#include "AnimationState.h"

struct InputFrame {
    Rectangle sprite;
    uint8_t duration;
};

struct AnimationFrame {
    Rectangle sprite;
    uint8_t triggerFrame;
};

class AnimatedSprite {
public:
    AnimatedSprite(std::vector<InputFrame> newFrames, uint32_t texture);
    Rectangle getSprite(AnimationState& state);
    uint32_t getTexture();
private:
    std::vector<AnimationFrame> frames;
    uint8_t totalFrames = 0;
    uint32_t texture;
};

#endif // ANIMATION_H