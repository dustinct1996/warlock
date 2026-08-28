#include "AnimatedSprite.h"
#include "Logging.h"
#include <algorithm>

AnimatedSprite::AnimatedSprite(std::vector<InputFrame> newFrames) {
    frames.reserve(4);

    for(uint32_t i = 0; i < newFrames.size(); i++) {
        AnimationFrame newFrame;

        newFrame.sprite = newFrames[i].sprite;
        newFrame.triggerFrame = totalFrames;
        totalFrames += newFrames[i].duration;

        frames.emplace_back(newFrame);
    }
}

Rectangle AnimatedSprite::getSprite(AnimationState& state) {
    Rectangle sprite;

    for(uint8_t i = 0; i < frames.size(); i++) {
        if(state.getFrameCounter() % totalFrames >= frames[i].triggerFrame) {
            sprite = frames[i].sprite;
        }
    }

    return sprite;
}