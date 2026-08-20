#include "Animation.h"
#include "Logging.h"
#include <algorithm>

Animation::Animation(std::vector<InputFrame> entityPayload) {
    frames.reserve(4);

    for(uint32_t i = 0; i < entityPayload.size(); i++) {
        AnimationFrame newFrame;

        newFrame.sprite = entityPayload[i].sprite;
        newFrame.triggerFrame = totalFrames;
        totalFrames += entityPayload[i].duration;

        frames.emplace_back(newFrame);
    }
}

SDL_Rect Animation::getSprite(AnimationState& state) {
    SDL_Rect sprite;

    for(uint8_t i = 0; i < frames.size(); i++) {
        if(state.getFrameCounter() % totalFrames >= frames[i].triggerFrame) {
            sprite = frames[i].sprite;
        }
    }

    return sprite;
}