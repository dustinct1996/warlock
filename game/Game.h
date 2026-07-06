#ifndef GAME_H
#define GAME_H

#include "Utils.h"
#include <vector>
#include "Camera.h"

struct InitConfig {
    std::string constantAssetsLocation;
    int windowWidth;
    int windowHeight;
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

#endif // GAME_H