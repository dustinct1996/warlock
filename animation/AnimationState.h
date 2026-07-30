#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

#include <SDL.h>

class AnimationState {
public:
    AnimationState();
    AnimationState(float frameIncrementationTrigger);
    void update(float timestep);
    unsigned int getFrameCounter();
private:
    float animationTimer_ = 0;
    float frameIncrementationTrigger_;
    unsigned int currentFrame_ = 0;
};

#endif // ANIMATIONSTATE_H