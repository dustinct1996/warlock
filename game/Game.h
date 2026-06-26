#pragma once

#include "Include.h"
#include <vector>
#include "Camera.h"

struct InitConfig {
    std::string assetsLocation;
};

class Game {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Game() = default;
    virtual ~Game() = default;
    virtual void init() = 0;
    virtual void update(const unsigned char* keys, float timestep) = 0;
    virtual void getRenderItems(std::vector<RenderItem>& renderItemsBuffer) = 0;
    
	Camera camera;
};