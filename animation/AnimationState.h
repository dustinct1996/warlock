#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

#include <SDL.h>

class AnimationState {
public:
    AnimationState();
    AnimationState(float frameIncrementationTrigger);
    void update(float timestep);
    uint32_t getFrameCounter();
private:
    float animationTimer = 0;
    float frameIncrementationTrigger;
    uint32_t currentFrame = 0;
};

#endif // ANIMATIONSTATE_H