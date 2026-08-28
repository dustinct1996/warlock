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
    AnimatedSprite(std::vector<InputFrame> newFrames);
    Rectangle getSprite(AnimationState& state);
    void print() {
        for(int i = 0; i < frames.size(); i++) {
            std::cout << "STARTING LOG..." << std::endl;
            std::cout << frames[i].sprite.x << " " << frames[i].sprite.y << std::endl;
            std::cout << frames[i].triggerFrame << std::endl;
        }
    };
private:
    std::vector<AnimationFrame> frames;
    uint8_t totalFrames = 0;
};

#endif // ANIMATION_H