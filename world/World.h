#include <vector>
#include <memory>
#include "Map.h"
#include "Entity.h"

class World {
public: 
    virtual void getProposedUpdates() = 0;
    virtual void commitUpdate() = 0;
    virtual void loadTextures() = 0;
    virtual void destroyTextures() = 0;

    std::vector<Map> maps;
    std::vector<std::unique_ptr<Entity>> renderEntities;
};