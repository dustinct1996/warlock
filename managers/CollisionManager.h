#include <SDL.h>
#include <utility>
#include <cmath>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Utils.h"
#include "Entity.h"

struct CollisionEntity {
    CollisionBox collisionBox;
    Point index;
};

class CollisionManager {
public:
    CollisionManager(Size bounds, int indices);

    void addEntity(CollisionBox collisionBox, uint32_t id);

    // void updateEntity(const Entity& worldEntity);

    void removeEntity(CollisionBox collisionBox, uint32_t id);

    // std::vector<const Entity&> findCollisions(const Entity& worldEntity);
private:
    // void findCollisionCandidates(const Entity& worldEntity);

    std::unordered_map<std::string, std::unordered_set<uint32_t>> collisionEntities;
    int worldWidth;
    int worldHeight;
    int indices;
};