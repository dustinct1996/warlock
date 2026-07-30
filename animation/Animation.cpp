#include "Animation.h"
#include "Logging.h"
#include <algorithm>

Animation::Animation(std::vector<InputFrame> entityPayload) {
    frames_.reserve(4);

    for(int i = 0; i < entityPayload.size(); i++) {
        AnimationFrame newFrame;

        newFrame.sprite = entityPayload[i].sprite;
        newFrame.triggerFrame = totalFrames_;
        totalFrames_ += entityPayload[i].duration;

        frames_.emplace_back(newFrame);
    }
}

SDL_Rect Animation::getSprite(AnimationState& state) {
    SDL_Rect sprite;

    for(unsigned char i = 0; i < frames_.size(); i++) {
        if(state.getFrameCounter() % totalFrames_ >= frames_[i].triggerFrame) {
            sprite = frames_[i].sprite;
        }
    }

    return sprite;
}