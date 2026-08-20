#include "CollisionManager.h"

CollisionManager::CollisionManager(Size bounds, int indices) {
    worldWidth = bounds.w;
    worldHeight = bounds.h;
    this->indices = indices;
}

void CollisionManager::addEntity(CollisionBox collisionBox, uint32_t id) {
    int gridWidth = worldWidth / indices;
    int gridHeight = worldHeight / indices;

    // LOG(INFO) << collisionBox.box.x << " " << collisionBox.box.w << " " << collisionBox.box.y << " " << collisionBox.box.h;
    // LOG(INFO) << worldWidth << " " << worldHeight << " " << indices;

    // LOG(INFO) << collisionEntities.size();

    CollisionBox cBox = collisionBox;

    Point topLeft{
        cBox.box.x / (float)(worldWidth / indices), 
        cBox.box.y / (float)(worldHeight / indices)
    };

    Point bottomRight{
        (cBox.box.x + cBox.box.w) / (float)(worldWidth / indices), 
        (cBox.box.y  + cBox.box.h) / (float)(worldHeight / indices)
    };

    for(int i = (int)topLeft.x; i <= (int)bottomRight.x; i++) {
        for(int j = (int)topLeft.y; j <= (int)bottomRight.y; j++) {
            collisionEntities[std::to_string(i) + std::to_string(j)].insert(id);
        }
    }

    // LOG(INFO) << collisionEntities.size();
    // LOG(INFO) << (int)topLeft.x << " " << (int)bottomRight.x << " " << (int)topLeft.y << " " << (int)bottomRight.y;
}

// void CollisionManager::updateEntity(const Entity& worldEntity) {
//     // compute and add tile index (x,y)
// }

void CollisionManager::removeEntity(CollisionBox collisionBox, uint32_t id) {
    int gridWidth = worldWidth / indices;
    int gridHeight = worldHeight / indices;

    // LOG(INFO) << collisionEntities.size();

    CollisionBox cBox = collisionBox;

    Point topLeft{
        cBox.box.x / (float)(worldWidth / indices), 
        cBox.box.y / (float)(worldHeight / indices)
    };

    Point bottomRight{
        (cBox.box.x + cBox.box.w) / (float)(worldWidth / indices), 
        (cBox.box.y  + cBox.box.h) / (float)(worldHeight / indices)
    };

    for(int i = (int)topLeft.x; i <= (int)bottomRight.x; i++) {
        for(int j = (int)topLeft.y; j <= (int)bottomRight.y; j++) {
            // if(!collisionEntities[std::to_string(i) + std::to_string(j)].empty() 
            //     && collisionEntities[std::to_string(i) + std::to_string(j)].find(id) != collisionEntities[std::to_string(i) + std::to_string(j)].end()) {
                collisionEntities[std::to_string(i) + std::to_string(j)].erase(id);
                // LOG(INFO) << "HI";
            // }
        }
    }

    // LOG(INFO) << collisionEntities.size();
}

// std::vector<const Entity&> CollisionManager::findCollisions(const Entity& worldEntity) {
//     std::vector<const Entity&> collisions = findCollisionCandidates(worldEntity);
// }

// void CollisionManager::findCollisionCandidates(const Entity& worldEntity) {
//     int gridWidth = worldWidth / indices;
//     int gridHeight = worldHeight / indices;

//     CollisionBox collisionBox = worldEntity.getCollisionBox();

//     Point topLeft(
//         collisionBox.x / (worldWidth / indices), 
//         collisionBox.y / (worldHeight / indices)
//     );

//     Point bottomRight(
//         (collisionBox.x + collisionBox.w) / (worldWidth / indices), 
//         (collisionBox.y  + collisionBox.h) / (worldHeight / indices)
//     );

//     for(int i = (int)topLeft.x; i < (int)bottomRight.x; i++) {
//         for(int j = (int)topLeft.y; j < (int)bottomRight.y; j++) {
//             collisionEntities[std::to_string(i) + std::to_string(j)].erase(worldEntity)
//         }
//     }
// }