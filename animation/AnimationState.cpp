#include "AnimationState.h"

AnimationState::AnimationState(): frameIncrementationTrigger(0.1) {}

AnimationState::AnimationState(float trigger): frameIncrementationTrigger(trigger) {}

void AnimationState::update(float timestep) {
    animationTimer += timestep;

    if (animationTimer >= frameIncrementationTrigger) {
        animationTimer = 0;
        currentFrame++;
    }
}

uint32_t AnimationState::getFrameCounter() {
    return currentFrame;
}