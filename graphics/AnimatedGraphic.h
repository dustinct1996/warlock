#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H

#include <vector>
#include <optional>
#include "AnimationState.h"

template <typename T>
class AnimatedGraphic : public Graphic {
private:
    struct AnimationFrame {
        T graphic;
        uint8_t triggerFrame;
    };
public:
    struct NewFrame {
        T graphic;
        uint8_t duration;
    };

    AnimatedGraphic(std::vector<NewFrame> newFrames) {
        for(uint32_t i = 0; i < newFrames.size(); i++) {
            frames.push_back(
                {
                    newFrames[i].graphic, 
                    totalFrames
                }
            );
            totalFrames += newFrames[i].duration;
        }
    }
    void render(Renderer& renderer, Point position, float zoom, AssetManager* assetManager = nullptr) override {
        frames[activeGraphic].graphic;
    };
    void setReflection(Reflection newReflection) {
        reflection = newReflection;
    }
    T& getActiveGraphic(AnimationState& state) {
        for(uint8_t i = 0; i < frames.size(); i++) {
            if(state.getFrameCounter() % totalFrames >= frames[i].triggerFrame) {
                activeGraphic = i;
            }
        }
        frames[activeGraphic].graphic.setReflection(reflection);
        return frames[activeGraphic].graphic;
    };
private:
    std::vector<AnimationFrame> frames;
    uint8_t totalFrames = 0;
    int activeGraphic = 0;
    Reflection reflection = Reflection::NONE;
};

#endif // ANIMATEDGRAPHIC_H