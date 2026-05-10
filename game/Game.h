#pragma once

#include "RenderItem.h"
#include <vector>

struct InitConfig {
    std::string assetsLocation;
};

class Game {
public:
    // Virtual classes need to have constructors and destructors explicitly defined.
    Game() = default;
    virtual ~Game() = default;
    virtual void init() = 0;
    virtual void update(const unsigned char* keys) = 0;
    virtual void getRenderItems(std::vector<RenderItem>& renderItemsBuffer) = 0;
};