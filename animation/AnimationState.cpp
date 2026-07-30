#include "AnimationState.h"

AnimationState::AnimationState(): frameIncrementationTrigger_(0.1) {}

AnimationState::AnimationState(float frameIncrementationTrigger): frameIncrementationTrigger_(frameIncrementationTrigger) {}

void AnimationState::update(float timestep) {
    animationTimer_ += timestep;

    if (animationTimer_ >= frameIncrementationTrigger_) {
        animationTimer_ = 0;
        currentFrame_++;
    }
}

unsigned int AnimationState::getFrameCounter() {
    return currentFrame_;
}